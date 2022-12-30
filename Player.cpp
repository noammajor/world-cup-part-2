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

int Player::get_cards() const
{
    return cards;
}

int Player::get_playerID() const
{
    return player_id;
}

void Player::add_games(int num)
{
    games_played += num;
}