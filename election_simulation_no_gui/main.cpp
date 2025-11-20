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
#include "nominee.hh"

using namespace std;

typedef const string command;

command ADD_NOMINEE = "a";
command QUIT_PROGRAM = "q";
command PRINT_NOMINEES = "p";
command SET_VOTES = "s";

const vector<string> ALL_COMMANDS =
    {ADD_NOMINEE, QUIT_PROGRAM, PRINT_NOMINEES};

void list_commands(){
    for (command &command_to_print : ALL_COMMANDS) {
        cout << command_to_print << endl;
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
        cout << nominee.get_name() << endl;
    }
}

bool set_votes_for_nominee(vector<Nominee> &nominees)
{
    string nominee_name;
    cout << "Give nominee's name: ";
    cin >> nominee_name;

    // Go through every nominee
    for (Nominee nominee : nominees)
    {
        // Check if a nominee's name mathches
        //
        if (nominee.get_name() == nominee_name) {
            unsigned int votes = 0;
            cout << "Nominee found. Set nominee's votes: ";
            cin >> votes;
            nominee.add_multiple_votes(votes);
        }
    }
}

int main()
{
    vector<Nominee> vector_of_nominees;
    cout << "Welcome to the election calculator. Right now implemented is transfrerable voting method" << endl;

    string chosen_command = "no command";

    while ( chosen_command != QUIT_PROGRAM)
    {
        list_commands();
        cout << "Insert a command: ";
        cin >> chosen_command;
        if (chosen_command == ADD_NOMINEE)
        {
            if (!add_nominee(vector_of_nominees)) {
               cout << "nominee adding failed" << endl;
            }
            continue;
        }

        if (chosen_command == PRINT_NOMINEES)
        {
            print_all_nominees(vector_of_nominees);
        }

        if (chosen_command == SET_VOTES)
        {
            set_votes_for_nominee(vector_of_nominees);
        }


    }

    cout << "Exiting program";

    return 0;
}
