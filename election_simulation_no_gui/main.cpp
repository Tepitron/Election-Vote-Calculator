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
Command READ_VOTES = {"r", "Reads votes from a file"};
Command SET_VOTES = {"s", "Set votes for one nominee"};
Command QUIT_PROGRAM = {"q", "Exits the program"};

const vector<Command> ALL_COMMANDS =
{
    ADD_NOMINEE, BEGIN_VOTING, CALCULATE_TRANSFERABLE,
    PRINT_NOMINEES, READ_VOTES, PRINT_COMMANDS,
    SET_VOTES, QUIT_PROGRAM
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

    if (nominee_name.empty()) {
        throw invalid_argument("No nominee name");
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

// Changes are made to the parameter itself
bool set_votes_for_nominee(vector<shared_ptr<Nominee>> &nominees)
{
    string nominee_name;
    cout << "Give nominee's name: ";
    cin >> nominee_name;

    // Go through every nominee
    for (shared_ptr<Nominee> nominee_ptr : nominees)
    {
        cout << "Going through nominees vector" << endl;

        // Check if a nominee's name mathches
        if (nominee_ptr->get_name() == nominee_name) {
            string votes;
            cout << "Nominee found. Set nominee's votes: ";
            cin >> votes;

            // Check if given string contains only numbers and isn't negative
            if (is_string_unsigned_number(votes))
            {
                vote_type votes_ul = stoul(votes);
                nominee_ptr->add_multiple_votes(votes_ul);
                return true;
            }
        }
    }
    return false;
}

// nominees contains all the nominees who are included in the voting.
// limit's type : const unsigned long.
// Limit is the threshold to stop the counting process

/*
void calculate_transferable_voting(vector<Nominee> nominees,
                                    const vote_type limit)
{
    vote_type min_votes;
}
*/

// Returns true if vote_row contains only digits, is unsigned
// and doesn't have duplicates.
bool validate_vote_row(string vote_row)
{
    // Uses regex to check for digit 0-9
    if (is_string_unsigned_number(vote_row))
    {

        vector<int> used_numbers;
        for (char digit_char : vote_row)
        {
            int digit = atoi(&digit_char);
            cout << "Checking digit: " << digit << endl;
            for (int used_number : used_numbers)
            {
                cout << "Used number: " << used_number;
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

// Changes are made to the parameter itself
void read_votes_from_file(vector<shared_ptr<Nominee>> &nominees)
{
    string file_path = "";
    cout << "Insert file path: ";
    cin >> file_path;

    ifstream vote_file(file_path);

    if (vote_file.is_open())
    {
        string vote_row;

        while (getline(vote_file, vote_row))
        {
            cout << vote_row << endl;
            validate_vote_row(vote_row);
        }

        vote_file.close();
    }
}

unsigned int Nominee::nominee_count = 0;
int main()
{
    vector<vector<unsigned int>> vote_rows;
    vector<shared_ptr<Nominee>> vector_of_nominees;
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

            if (chosen_command == PRINT_NOMINEES.command)
            {
                print_all_nominees(vector_of_nominees);
            }

            if (chosen_command == SET_VOTES.command)
            {
                set_votes_for_nominee(vector_of_nominees);
            }

            if (chosen_command == PRINT_COMMANDS.command)
            {
                list_commands();
            }

            if (chosen_command == READ_VOTES.command)
            {
                read_votes_from_file(vector_of_nominees);
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
