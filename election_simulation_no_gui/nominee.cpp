#include "nominee.hh"
#include <iostream>

Nominee::Nominee(string name)
{
    cout << "Constructor called for " << name << endl;
    nominee_count++;
    _vote_count = 0, _name = name,
    _nominee_number = nominee_count;
}

Nominee::~Nominee()
{
    cout << "Destructor called" << endl;
    nominee_count--;
}

void Nominee::add_vote()
{
    _vote_count++;
}

void Nominee::add_multiple_votes(vote_type new_votes)
{
    _vote_count += new_votes;
}

void Nominee::remove_votes(vote_type votes_to_remove)
{
    if (votes_to_remove <= _vote_count)
    {
        _vote_count -= votes_to_remove;
    }
}

vote_type Nominee::get_vote_count()
{
    return _vote_count;
}

string Nominee::get_name()
{
    return _name;
}

unsigned int Nominee::get_nominee_number()
{
    return _nominee_number;
}
