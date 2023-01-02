#include "UF.h"



UF::UF()
{
    players_table = new Hash_table();
    teams_tree = new AVL_Tree<Team*,TeamIDOrder>();
}

UF::~UF()
{
    delete players_table;
    delete teams_tree;
}

int UF::get_sum_games(int id) const
{
    return players_table->get_games(id);
}

void UF::pre_des()
{
    players_table->destroy();
}


bool UF::teamExists(int teamID) const
{
    if(!teams_tree->search(teamID))
    {
        return false;
    }
    else
        return true;
}

bool UF::addTeam(Team* team)
{
    return teams_tree->insert_to_tree(team);
}


bool UF::removeTeam(int id)
{
    UF_Node* players = teams_tree->search(id)->get_data_Node()->get_players();
    if (players)
        players->team = nullptr;
    return teams_tree->remove(id);
}


int UF::get_team_points(int id) const
{
   return teams_tree->search(id)->get_data_Node()->get_points();
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
    node1->team = nullptr;
    UF_Node* root = team1->get_players();
    if (root)
    {
        node1->father = root;
        player1->add_games(-root->player->get_games_played());
        player1->change_per_right(root->player->get_per().inv());
        root->size++;
    }
    else
    {
        node1->father = nullptr;
        node1->team = team1;
        team1->add_first_player(node1);
    }
}


UF_Node* UF::Union(UF_Node* r1, UF_Node* r2)
{
    if (r1 == r2)
        return r1;
    if (!r2)
        return r1;
    if (!r1)
    {
        return r2;
    }
    if (r1->size > r2->size)
    {
        r2->father = r1;
        r2->team = nullptr;
        r2->player->add_games(-r1->player->get_games_played());
        r2->player->change_per_right(r1->player->get_per().inv());
        r1->size += r2->size;
        return r1;
    }
    else
    {
        r1->father = r2;
        r1->team = nullptr;
        r1->player->add_games(-r2->player->get_games_played());
        r1->player->change_per_right(r2->player->get_per().inv());
        r2->size += r1->size;
        return r2;
    }
}


Team* UF::find(int key)
{
    Pocket* pocket1 = this->players_table->get(key);
    if(!pocket1)
    {
        return nullptr;
    }
    UF_Node* rootNode = pocket1->node;
    int cur_games;
    int tot_games = rootNode->player->get_games_played();
    permutation_t cur_per;
    permutation_t tot_per = rootNode->player->get_per();
    while(rootNode->father)
    {
        tot_games += rootNode->father->player->get_games_played();
        tot_per = tot_per * rootNode->father->player->get_per();
        rootNode = rootNode->father; // hold top of the group
    }
    int root_games = rootNode->player->get_games_played();
    permutation_t root_per = rootNode->player->get_per();
    UF_Node* tempSqueezeLines1 = pocket1->node;
    UF_Node* tempSqueezeLines2;
    while(tempSqueezeLines1->father)
    {
        cur_games = tempSqueezeLines1->player->get_games_played();
        tempSqueezeLines1->player->add_games(tot_games - cur_games - root_games);
        cur_per = tempSqueezeLines1->player->get_per();
        tempSqueezeLines1->player->change_per_right(cur_per.inv() * tot_per * root_per.inv());
        tempSqueezeLines2 = tempSqueezeLines1->father;
        tempSqueezeLines1->father = rootNode;
        tempSqueezeLines1 = tempSqueezeLines2;
        tot_games -= cur_games;
        tot_per = cur_per.inv() * tot_per;
    }
    if (rootNode->team)
        return rootNode->team;
    return nullptr;
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
    if(!players_table->get(key))
        return nullptr;
    else
        return players_table->get(key)->node->player;
}


