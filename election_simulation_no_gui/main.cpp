/*
 * ELECTION CALCULATOR
 *
 *  This program calculates votes for
 *  elections using transferable voting method.
 *  The user gives the nominees' names and
 *  puts in the votes. Then the user gives
 *  a maximum number of votes to surpass for
 *  a quicker win.
 *  Then the program goes through
 *  the elimination steps, if the limit hasn't been reached.
 *
 *  COMMANDS:
 *  a - Adds a nominee.
 *  b - Begin the voting. Every nominee is voted on. 1 is the first choice
 *      2 is the second choice, 3 the third choice, all the way to the last
 *      nominee.
 *  c - Calculates the results using the transferable voting method.
 *      Votes are calculated until one nominee reaches the set limit amount
 *      of votes. By default the limit is half of all the votes.
 *      If the limit isn't reached, the nominee with the lowest amount of votes
 *      is eliminated and the calculation begins again.
 *  p - Print all nominees
 *  r - Read votes from a file
 *  s - Sets votes
 *  h - Lists all commands
 */

#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <memory>
#include <fstream>
#include "nominee.hh"

using namespace std;

struct Command{
    string command;
    string description;
};

Command ADD_NOMINEE = {"a", "Add a new nominee"};
Command BEGIN_VOTING = {"b", "Give votes to nominees"};
Command CALCULATE_TRANSFERABLE = {"c", "Calculate results with"
                                       " the transferable voting method"};
Command PRINT_COMMANDS = {"help", "Lists all available commands"};
Command PRINT_NOMINEES = {"p", "Prints out all nominees"};
Command READ_NOMINEES = {"n", "Reads nominee names from a file"};
Command READ_VOTES = {"r", "Reads votes from a file"};
Command SET_LIMIT = {"l", "Set limit for the vote calculator"};
Command QUIT_PROGRAM = {"q", "Exits the program"};

const int MAX_NAME_LENGTH = 20;

const vector<Command> ALL_COMMANDS =
{
    ADD_NOMINEE, BEGIN_VOTING, CALCULATE_TRANSFERABLE,
    PRINT_NOMINEES, READ_VOTES, PRINT_COMMANDS,
    QUIT_PROGRAM
};

void list_commands(){
    for (auto &command_to_print : ALL_COMMANDS) {
        cout << command_to_print.command << " " <<
            command_to_print.description << endl;
    }
}

// Nominee is added to the vector that the parameter references
void add_nominee(vector<shared_ptr<Nominee>> &all_nominees)
{
    string nominee_name;
    cout << "Insert nominee's name: ";
    cin >> nominee_name;

    // Shouldn't happen because cin doesn't take empty input
    if (nominee_name.empty()) {
        throw invalid_argument("No nominee name");
    }

    // Throws error if nominee name is too long
    else if (nominee_name.length() > MAX_NAME_LENGTH)
    {
        throw invalid_argument("Nominee name too long");
    }

    // Makes a unique pointer from nominee and pushes it into the all
    // nominees vector
    shared_ptr<Nominee> new_nominee_ptr(new Nominee(nominee_name));
    all_nominees.push_back(new_nominee_ptr);
}

void print_all_nominees(vector<shared_ptr<Nominee>> &nominees)
{
    for (shared_ptr<Nominee> nominee_ptr : nominees)
    {
        cout << "Nominee " << nominee_ptr->get_nominee_number() << " " <<
            nominee_ptr->get_name() << endl;
    }
}

// Returns true if input string contains only digits
bool is_string_unsigned_number(string inputted_string)
{
    regex digit_check("[0-9]+");
    return (regex_match(inputted_string, digit_check));
}

bool validate_vote_row(string vote_row)
{
    // Uses regular expression to check for digits 0-9
    if (is_string_unsigned_number(vote_row))
    {

        vector<int> used_numbers;
        for (char digit_char : vote_row)
        {
            int digit = atoi(&digit_char);
            for (int used_number : used_numbers)
            {
                if (used_number == digit)
                {
                    cout << "Read vote_row contains double digits. "
                         << "Doubled digit: " << digit << endl;
                    return false;
                }
            }
            used_numbers.push_back(digit);
        }
        return true;
    }
    cout << "Not unsigned vote_row" << endl;
    return false;
}

vector<vector<unsigned int>> read_votes_from_file()
{
    vector<vector<unsigned int>> all_votes_from_file;
    string file_path = "";
    cout << "Insert file path: ";
    cin >> file_path;

    ifstream vote_file(file_path);

    if (vote_file.is_open())
    {
        string vote_row;

        while (getline(vote_file, vote_row))
        {
            vector<unsigned int> vote_row_uint;
            cout << vote_row << endl;
            if (validate_vote_row(vote_row))
            {
                for (char digit_char : vote_row)
                {
                    unsigned int digit = atoi(&digit_char);
                    vote_row_uint.push_back(digit);
                }
                all_votes_from_file.push_back(vote_row_uint);
            }
        }
        vote_file.close();
    }
    else{
        cout << "File reading error" << endl;
    }
    return all_votes_from_file;
}

void transferable_voting_calculation(vector<vector<unsigned int>> vote_rows,
                                     vector<shared_ptr<Nominee>> nominees,
                                     unsigned int limit,
                                     unsigned int vote_round)
{

    // Counts the initial votes
    for (const vector<unsigned int> &vote_row : vote_rows)
    {
        unsigned int index = 0;
        for (unsigned int digit : vote_row)
        {
            if (digit == vote_round)
            {
                nominees[index]->add_vote();
                break;
            }
            index++;
        }
    }

    shared_ptr<Nominee> leading_nominee_ptr = nominees[0];
    cout << "Vote after first round:" << endl;
    for (auto nominee_ptr : nominees)
    {
        if (nominee_ptr->get_vote_count() > leading_nominee_ptr->get_vote_count())
        {
            leading_nominee_ptr = nominee_ptr;
        }
        cout << "Nominee: " << nominee_ptr->get_name() <<
            " " << nominee_ptr->get_nominee_number() <<
            " has " << nominee_ptr->get_vote_count() <<
            " amount of votes" << endl << endl;
    }
    cout << "Leader is " << leading_nominee_ptr->get_name()
         << " with " << leading_nominee_ptr->get_vote_count()
         << " votes" << endl;

}

unsigned int set_limit()
{
    unsigned int limit;
    cout << "Set limit for the voting calculator to stop at: ";
    cin >> limit;
    return limit;
}

void read_nominees_from_file(vector<shared_ptr<Nominee>> &nominees)
{
    string file_path = "";
    cout << "Input file path: ";
    cin >> file_path;

    ifstream nominee_file(file_path);

    if (nominee_file.is_open())
    {
        string nominee_name;
        while (getline(nominee_file, nominee_name))
        {
            shared_ptr<Nominee> new_nominee_ptr(new Nominee(nominee_name));
            nominees.push_back(new_nominee_ptr);
        }
        nominee_file.close();
    }
    else
    {
        cout << "Error reading nominee file" << endl;
    }
}

unsigned int Nominee::nominee_count = 0;
int main()
{
    vector<vector<unsigned int>> vote_rows;
    vector<shared_ptr<Nominee>> vector_of_nominees;
    unsigned int vote_end_limit = 0;
    cout << "Welcome to the election calculator. Right now implemented is transrerable voting method" << endl;

    string chosen_command = "no command";
    list_commands();
    // Commands are asked until user inputs the quit command.
    while ( chosen_command != QUIT_PROGRAM.command)
    {
        cout << "Insert a command: ";
        cin >> chosen_command;
        try
        {
            if (chosen_command == ADD_NOMINEE.command)
            {
                add_nominee(vector_of_nominees);
            }

            if (chosen_command == CALCULATE_TRANSFERABLE.command)
            {
                transferable_voting_calculation(vote_rows,
                                                vector_of_nominees,
                                                vote_end_limit,
                                                1);
            }

            if (chosen_command == PRINT_NOMINEES.command)
            {
                print_all_nominees(vector_of_nominees);
            }

            if (chosen_command == PRINT_COMMANDS.command)
            {
                list_commands();
            }

            if (chosen_command == READ_VOTES.command)
            {
                vote_rows = read_votes_from_file();
            }

            if (chosen_command == READ_NOMINEES.command)
            {
                read_nominees_from_file(vector_of_nominees);
            }

            if (chosen_command == SET_LIMIT.command)
            {
                vote_end_limit = set_limit();
            }
        }
        catch (const invalid_argument& e)
        {
            cout << "Caught exception: " << e.what();
        }

        catch (...)
        {
            cout << "Caught an unknown exception" << endl;
        }
    }

    cout << "Exiting program";

    return 0;
}
