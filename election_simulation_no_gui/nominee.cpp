#include "nominee.hh"

Nominee::Nominee() {
    _vote_count = 0, _name = "NO NAME";
}

Nominee::Nominee(string name)
{
    _name = name;
}

Nominee::~Nominee()
{

}

void Nominee::add_vote()
{
    _vote_count++;
}

void Nominee::add_multiple_votes(unsigned int new_votes)
{
    _vote_count += new_votes;
}

void Nominee::remove_votes(unsigned int votes_to_remove)
{
    if (votes_to_remove <= _vote_count)
    {
        _vote_count -= votes_to_remove;
    }

}

unsigned int Nominee::get_vote_count()
{
    return _vote_count;
}

string Nominee::get_name()
{
    return _name;
}
