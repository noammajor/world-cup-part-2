#ifndef UF_H
#define UF_H

#include "hash.h"
#include "AVL_tree.h"
#include "Team.h"
#include "Player.h"




class UF
{
    Hash_table* players_table;
    AVL_Tree<Team*, TeamAbilityOrder>* teams_tree;

public:
    UF(): players_table(new Hash_table), teams_tree(new AVL_Tree<Team,TeamID>){}
    UF& operator=(const UF&) = delete;
    UF(const UF&) = delete;
    ~UF() = default; ////////////////////////do later

    Player* player_exists(int key) const;
    void insert(Player* elem, Team* group);
    void Union(UF_Node* r1, UF_Node* r2);
    G* find(int key);
    bool connected(Player* elem1, Player* elem2) const;
    bool addTeam(int id);
    bool removeTeam(int id);
    T* getPlayer(int id);
    bool teamExists(int teamID) const;
    permutation_t getTeamPermutation() const;
    Team* get_team(int teamID) const;

};

#endif //UF_H
