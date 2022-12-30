#include "Team.h"


void Team::add_ability(int amount)
{
    players_ability += amount;
}

int Team::get_ID () const
{
    return this->teamID;
}

void Team::add_points(int points_add)
{
    points += points_add;
}

int Team::get_ability() const
{
    return players_ability;
}

UF_Node* Team::get_players() const
{
    return playersUF;
}

void Team::add_first_player(UF_Node*  p1)
{
    playersUF = p1;
}

bool Team::operator >(const Team* p1) const
{
    if(p1->teamID  < this->teamID)
    {
        return true;
    }
    else
        return false;
}

permutation_t Team::get_per() const
{
    return amount;
}

void Team::change_per_right( const permutation_t& p)
{
    amount = amount * p;
}

void Team::change_per_left( const permutation_t& p)
{
    amount = p * amount;
}

int Team::get_points() const
{
    return points;
}

int Team::get_num_goalkeepers() const
{
    return num_goalkeepers;
}

void Team::add_goalkeepers(int num)
{
    num_goalkeepers += num;
}

bool TeamIDOrder::operator()(const Team* t1, const Team* t2) const
{
    return t1->get_ID() > t2->get_ID();
}

bool TeamIDOrder::operator()(const Team* t1, int num) const
{

    return t1->get_ID() > num;
}

bool TeamIDOrder::operator()(int num, const Team* t1) const
{

    return num > t1->get_ID();
}

bool TeamAbilityOrder::operator()(const Team* t1, const Team* t2) const
{
    if (t1->get_ability() > t2->get_ability())
        return true;
    else if (t1->get_ability() < t2->get_ability())
        return false;
    else
        return t1->get_ID() > t2->get_ID();
}

