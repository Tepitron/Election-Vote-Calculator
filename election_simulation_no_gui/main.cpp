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
 *  p - Print all nominees
 *  s - Sets votes
 */

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <memory>
#include "nominee.hh"

using namespace std;

struct Command{
    string command;
    string description;
};

Command ADD_NOMINEE = {"a", "Add a new nominee"};
Command CALCULATE_TRANSFERABLE = {"c", "Calculate results with"
                                       " the transferable voting method"};
Command PRINT_COMMANDS = {"help", "Lists all available commands"};
Command PRINT_NOMINEES = {"p", "Prints out all nominees"};
Command SET_VOTES = {"s", "Set votes for one nominee"};
Command QUIT_PROGRAM = {"q", "Exits the program"};

const vector<Command> ALL_COMMANDS =
{
    ADD_NOMINEE, PRINT_NOMINEES, PRINT_COMMANDS,
    SET_VOTES, QUIT_PROGRAM
};

void list_commands(){
    for (auto &command_to_print : ALL_COMMANDS) {
        cout << command_to_print.command << " " <<
            command_to_print.description << endl;
    }
}

bool add_nominee(vector<shared_ptr<Nominee>> &all_nominees)
{
    string nominee_name;
    cout << "Insert nominee's name: ";
    cin >> nominee_name;

    if (nominee_name.empty()) {
        return false;
    }

    // Makes a unique pointer from nominee and pushes it into the all
    // nominees vector
    shared_ptr<Nominee> new_nominee_ptr(new Nominee(nominee_name));
    all_nominees.push_back(new_nominee_ptr);

    return true;
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
    if (regex_match(inputted_string, digit_check)){
        cout << "It's a match" << endl;
        return true;
    }
    cout << "No match" << endl;
    return false;
}

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


unsigned int Nominee::nominee_count = 0;
int main()
{
    vector<shared_ptr<Nominee>> vector_of_nominees;
    cout << "Welcome to the election calculator. Right now implemented is transrerable voting method" << endl;

    string chosen_command = "no command";
    list_commands();
    // Commands are asked until user inputs the quit command.
    while ( chosen_command != QUIT_PROGRAM.command)
    {
        cout << "Insert a command: ";
        cin >> chosen_command;
        if (chosen_command == ADD_NOMINEE.command)
        {
            if (!add_nominee(vector_of_nominees)) {
               cout << "nominee adding failed" << endl;
            }
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
    }

    cout << "Exiting program";

    return 0;
}
