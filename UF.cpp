#include "AVL_tree.h"
#include "UF.h"




permutation_t UF::getTeamPermutation() const
{



}

bool UF::teamexists(int teamid) const
{
    if(groups->search(teamid)==nullptr)
    {
        return true;
    }
    else
        return false;
}

bool UF::addTeam(int id)
{
    return groups->insert_to_tree(id);
}


bool UF::removeTeam(int id)
{
    return groups->remove(id);
}


Player* UF::getPlayer(int id)
{
    Pocket* temp = elements->get(id);
    if(temp == nullptr)
    {
        return nullptr;
    }
    return temp->node->data;
}


void UF::insert(Player* elem, Team* group)
{
    UF_Node node1 = new UF_Node(elem);
    elements->add(elem->get_playerID(), node1);
    node1->group = group;
    UF_Node root = group->get_elements();/////////
    node1.father = root;
    root->size++;

    // elem->partial_spirit += team_spirit

    return true;
}


bool UF::connected(Player* elem1, Player* elem2) const
{
    return (this->find(elem1) == this->find(elem2));
}


void UF::Union(Team* g1, Team* g2)
{
    if (g1->get_ID() == g2->get_ID())
        return;
    UF_Node root1 = g1->get_elements();
    UF_Node root2 = g2->get_elements();
    if (root1->size > g2->size)
    {
        root2->father = root1;
        root1->size += root2->size;
    }
    else
    {
        root1->father = root2;
        root2->size += root1->size;
    }
}


Team* UF::find(int key)
{
    Pocket* pocket1 = this->elements.get(key);
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
    return rootNode->group;
}

Team* UF::get_team(int teamID)
{
    Node<Team, TeamIDOrder> node* = groups->search(teamID);
    if (!node)
        return nullptr;
    return node->get_data_Node();
}
Player* UF::player_exists(int key) const
{
    if(elements->get(key)== nullptr)
    {
        return nullptr
    }
    else
        return elements->get(key)->node->data;
}


