#include "Team.h"

Team::Team(int ID): teamID(ID), points(points), num_goalkeepers(0), playersUF(nullptr){}


int Team::get_num_goalkeepers() const
{
    return num_goalkeepers;
}
void Team::add_ability(int amount)
{
    players_ability+=amount;
}
int Team::get_ID () const
{
    return this->teamID;
}

void Team::add_points(int points_add)
{
    points += points_add;
}

void Team::more_game_played()
{
    playersUF->player->add_game();
}

void Team::add_player (Player* player)
{
    if (player->is_goalkeeper())
        num_goalkeepers++;
    players_ability += player->get_ability();
}

bool Team::is_legal() const
{
    if (num_goalkeepers > 0)
        return true;
    return false;
}

int Team::get_ability() const
{
    return players_ability;
}

UF_Node* Team::get_players() const
{

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

void Team::change_per( const permutation_t& p)
{
    amount=amount*p;
}
int Team::tot_game_points() const
{
    return points + players_ability;
}

int Team::get_points() const
{
    return points;
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
    return t1->get_ability() > t2->get_ability();
}

bool TeamAbilityOrder::operator()(const Team* t1, int num) const
{

    return t1->get_ability() > num;
}

bool TeamAbilityOrder::operator()(int num, const Team* t1) const
{

    return num > t1->get_ability();
}
