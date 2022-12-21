#include "AVL_tree.h"
#include "UF.h"




permutation_t UF::getTeamPermutation() const
{



}






bool UF::teamExists(int teamID) const
{
    if(teams_tree->search(teamID)==nullptr)
    {
        return true;
    }
    else
        return false;
}

bool UF::addTeam(int id)
{
    return teams_tree->insert_to_tree(id);
}


bool UF::removeTeam(int id)
{
    return teams_tree->remove(id);
}


Player* UF::getPlayer(int id)
{
    Pocket* temp = players_table->get(id);
    if(temp == nullptr)
    {
        return nullptr;
    }
    return temp->node->player;
}


void UF::insert(Player* player1, Team* team1)
{
    UF_Node* node1 = new UF_Node(player1);
    players_table->add(player1->get_playerID(), node1);
    node1->team = team1;
    UF_Node* root = team1->get_players();/////////
    node1->father = root;
    root->size++;

    // elem->partial_spirit += team_spirit

}


bool UF::connected(Player* elem1, Player* elem2) const
{
    return (this->find(elem1) == this->find(elem2));
}


void UF::Union(UF_Node* r1, UF_Node* r2)
{
    if (r1 == r2)
        return;
    if (r1->size > r2->size)
    {
        r2->father = r1;
        r1->size += r2->size;
    }
    else
    {
        r1->father = r2;
        r2->size += r1->size;
    }
}


Team* UF::find(int key)
{
    Pocket* pocket1 = this->players_table->get(key);
    if(pocket1 == nullptr)
    {
        return nullptr;
    }
    UF_Node* rootNode = pocket1->node;
    while(rootNode->father != nullptr)
    {
        rootNode = rootNode->father; // hold top of the group
    }
    UF_Node* tempSqueezeLines1 = pocket1->node;
    UF_Node* tempSqueezeLines2 = pocket1->node;
    while(tempSqueezeLines1->father != nullptr)
    {
        tempSqueezeLines2 = tempSqueezeLines1->father;
        tempSqueezeLines1->father = rootNode;
        tempSqueezeLines1 = tempSqueezeLines2;
    }
    return rootNode->team;
}

Team* UF::get_team(int teamID) const
{
    Node<Team*, TeamIDOrder>* node = teams_tree->search(teamID);
    if (!node)
        return nullptr;
    return node->get_data_Node();
}

Player* UF::player_exists(int key) const
{
    if(players_table->get(key)== nullptr)
    {
        return nullptr
    }
    else
        return players_table->get(key)->node->player;
}


