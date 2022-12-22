#ifndef TEAM_H
#define TEAM_H

#include "AVL_tree.h"
#include "Player.h"
#include "wet2util.h"
#include "UF.h"

template<class T, class Cond>
class AVL_Tree;

class Team
{
    int teamID;
    int points;
    int num_goalkeepers;
    int players_ability;
    UF_Node* playersUF;
    permutation_t amount;


public:
    Team(int ID);

    Team& operator=(const Team&) = delete;

    Team(const Team&) = delete;

    ~Team() = default;

    int get_ID () const;

    void add_ability(int amount);

    void add_player (Player* player);

    bool operator >(const Team* p1) const;

    int tot_game_points() const;

    int get_points() const;

    void add_points(int pointsAdd);

    bool exists_goalkeeper() const;

    void more_game_played();

    int get_ability() const;

    permutation_t get_per() const;

    void change_per( const permutation_t& p);

    UF_Node* get_players() const;

    void add_first_player(UF_Node*  p1);
};

class TeamIDOrder
{
public:
    bool operator()(const Team* t1, const Team* t2) const;
    bool operator()(const Team* t1, int num) const;
    bool operator()(int num, const Team* t1) const;

};

class TeamAbilityOrder
{
public:
    bool operator()(const Team* t1, const Team* t2) const;

};

#endif //TEAM_H
