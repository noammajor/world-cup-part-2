#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Team.h"
#include "wet2util.h"

class Team;

class Player
{
    int player_id;
    int games_played;
    int cards;
    bool goalkeeper;
    int teamsGamesPlayed;
    int ability;
    permutation_t partial_spirit;


public:


    Player(int playerId, int gamesPlayed,int ability, int cards, bool goalKeeper,const permutation_t &spirit):player_id(playerId),ability
    (ability),games_played(gamesPlayed),cards(cards),goalkeeper(goalKeeper),partial_spirit(spirit){};

    ~Player() = default;

    Player &operator=(const Player &player) = delete;

    Player(const Player &player) = delete;


    int get_games_played() const;

    bool is_goalkeeper() const;

    int get_cards() const;

    int get_playerID() const;

    int get_team_games() const;

    void add_games(int num);

    int get_ability() const;

    permutation_t get_per() const;

    void change_per_right( const permutation_t& p);

    void change_per_left( const permutation_t& p);

    void add_cards(int cards);

};




#endif //PLAYER_H