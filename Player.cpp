#include <iostream>
#include "Team.h"
#include "Player.h"


int Player::get_games_played() const
{
    return this->games_played;
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

void Player::add_game()
{
    games_played++;
}

int Player::get_ability() const
{
    return ability;
}