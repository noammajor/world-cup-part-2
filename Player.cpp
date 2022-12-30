#include <iostream>
#include "Team.h"
#include "Player.h"



void Player::add_cards(int cards)
{
    this->cards += cards;
}

int Player::get_games_played() const
{
    return this->games_played;
}

permutation_t Player::get_per() const
{
    return partial_spirit;
}

void Player::change_per_right(const permutation_t &p)
{
    partial_spirit = partial_spirit*p;
}
void Player::change_per_left(const permutation_t &p)
{
    partial_spirit = p*partial_spirit;
}


bool Player::is_goalkeeper() const
{
    return goalkeeper;
}


int Player::get_cards() const
{
    return cards;
}

int Player::get_playerID() const
{
    return player_id;
}

int Player::get_team_games() const
{
    return teamsGamesPlayed;
}

void Player::add_games(int num)
{
    games_played += num;
}

int Player::get_ability() const
{
    return ability;
}