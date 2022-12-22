#ifndef UF_H
#define UF_H

#include "hash.h"
#include "AVL_tree.h"
#include "Team.h"
#include "Player.h"


class TeamIDOrder;

class Team;

class Player;

class Hash_table;

class UF_Node;


class UF
{
    Hash_table* players_table;
    AVL_Tree<Team*, TeamIDOrder>* teams_tree;

public:
    UF();
    UF& operator=(const UF&) = delete;
    UF(const UF&) = delete;
    ~UF() = default; ////////////////////////do later
    bool is_in_tor(int id) const;
    Player* player_exists(int key) const;
    void insert(Player* elem, Team* group);
    void Union(UF_Node* r1, UF_Node* r2);
    Team* find(int key);
    bool addTeam(Team* team);
    bool removeTeam(int id);
    Player* getPlayer(int id);
    bool teamExists(int teamID) const;
    Team* get_team(int teamID) const;
    int get_sum_games(int id) const;
    int get_team_points(int id) const;

};



#endif //UF_H
