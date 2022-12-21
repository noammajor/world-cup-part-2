#ifndef UF_H
#define UF_H

#include "hash.h"
#include "AVL_tree.h"
#include "Team.h"
#include "Player.h"




class UF
{
    Hash_table* elements;
    AVL_Tree<Team, TeamID>* groups;

public:
    UF(): elements(new Hash_table), groups(new AVL_Tree<Team,TeamID>){}
    UF& operator=(const UF&) = delete;
    UF(const UF&) = delete;
    ~UF() = default; ////////////////////////do later

    void insert(Player* elem, Team* group);
    void Union(Team* g1, Team* g2);
    G* find(int key);
    bool connected(Player* elem1, Player* elem2) const;
    bool addTeam(int id);
    bool removeTeam(int id);
    T* getPlayer(int id);
    bool teamexists(int teamid) const;
    permutation_t getTeamPermutation() const;


};

#endif //UF_H
