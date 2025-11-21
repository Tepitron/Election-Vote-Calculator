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
#include "nominee.hh"

using namespace std;

struct Command{
    string command;
    string description;
};

Command ADD_NOMINEE = {"a", "Add a new nominee"};
Command PRINT_NOMINEES = {"p", "Prints out all nominees"};
Command SET_VOTES = {"s", "Set votes for one nominee"};
Command QUIT_PROGRAM = {"q", "Exits the program"};

/*const string ADD_NOMINEE = "a";
const string QUIT_PROGRAM = "q";
const string PRINT_NOMINEES = "p";
const string SET_VOTES = "s";
*/

const vector<Command> ALL_COMMANDS =
{
    ADD_NOMINEE, PRINT_NOMINEES, SET_VOTES, QUIT_PROGRAM
};

void list_commands(){
    for (auto &command_to_print : ALL_COMMANDS) {
        cout << command_to_print.command << " " <<
            command_to_print.description << endl;
    }
}

bool add_nominee(vector<Nominee> &all_nominees)
{
    string nominee_name;
    cout << "Insert nominee's name: ";
    cin >> nominee_name;

    Nominee new_nominee (nominee_name);
    all_nominees.push_back(new_nominee);

    return true;
}

void print_all_nominees(vector<Nominee> &nominees)
{
    for (Nominee nominee : nominees)
    {
        cout << "Nominee " << nominee.get_nominee_number() << " " <<
            nominee.get_name() << endl;
    }
}

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

bool set_votes_for_nominee(vector<Nominee> &nominees)
{
    string nominee_name;
    cout << "Give nominee's name: ";
    cin >> nominee_name;

    // Go through every nominee
    for (auto nominee : nominees)
    {
        cout << "Going through nominees vector" << endl;
        // Check if a nominee's name mathches

        if (nominee.get_name() == nominee_name) {
            string votes;
            cout << "Nominee found. Set nominee's votes: ";
            cin >> votes;

            if (is_string_unsigned_number(votes))
            {
                vote_type votes_ul = stoul(votes);
                nominee.add_multiple_votes(votes_ul);
            }
        }
    }
}

int main()
{
    vector<Nominee> vector_of_nominees;
    cout << "Welcome to the election calculator. Right now implemented is transrerable voting method" << endl;

    string chosen_command = "no command";

    while ( chosen_command != QUIT_PROGRAM.command)
    {
        list_commands();
        cout << "Insert a command: ";
        cin >> chosen_command;
        if (chosen_command == ADD_NOMINEE.command)
        {
            if (!add_nominee(vector_of_nominees)) {
               cout << "nominee adding failed" << endl;
            }
            continue;
        }

        if (chosen_command == PRINT_NOMINEES.command)
        {
            print_all_nominees(vector_of_nominees);
        }

        if (chosen_command == SET_VOTES.command)
        {
            set_votes_for_nominee(vector_of_nominees);
        }

    }

    cout << "Exiting program";

    return 0;
}
