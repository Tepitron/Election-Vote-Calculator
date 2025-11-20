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

class Nominee
{
public:
    // Constructors
    Nominee();
    Nominee(string name);
    // Destructor
    ~Nominee();
    // Raises vote count by 1
    void add_vote();
    // Raises vote count by x amount
    void add_multiple_votes(unsigned int new_votes);
    // Decreases vote count by x amount
    void remove_votes(unsigned int votes_to_remove);
    // Getter for vote count
    unsigned int get_vote_count();
    // Getter for name
    string get_name();

private:
    // Nominee's name
    string _name;
    // Nominee's count of votes
    unsigned int _vote_count;
};

#endif // NOMINEE_HH
