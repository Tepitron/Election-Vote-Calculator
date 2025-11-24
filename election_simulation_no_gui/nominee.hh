/*
 * Nominee in the elections.
 * Has a name and a vote count.
 * These can both be changed publicly.
 *
 * */

#ifndef NOMINEE_HH
#define NOMINEE_HH

#include <string>

using namespace std;

typedef unsigned long vote_type;

class Nominee
{
public:
    // Constructors
    Nominee(string name);
    // Destructor
    ~Nominee();
    // Raises vote count by 1
    void add_vote();
    // Raises vote count by x amount
    void add_multiple_votes(vote_type new_votes);
    // Decreases vote count by x amount
    void remove_votes(vote_type votes_to_remove);
    // Getter for vote count
    vote_type get_vote_count();
    // Getter for name
    string get_name();
    // Getter for nominee number
    unsigned int get_nominee_number();
    // Returns count of nominees
    unsigned int get_nominee_count();

private:
    // Nominee's name
    string _name;
    // Nominee's count of votes
    vote_type _vote_count;
    // Nominee's vote number
    unsigned int _nominee_number;
    // Counts the amount of each nominee object
    static unsigned int nominee_count;
};

#endif // NOMINEE_HH
