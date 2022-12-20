#include "Team.h"

Team::Team(int ID, int points): teamID(ID), points(points), num_players(0), num_goalkeepers(0),
                                tot_goals_cards(0),games_played(0), players()
{
    players = new AVL_Tree<Player*, Player::PlayerIDOrder>;
    playerGoal = new AVL_Tree<Player*, Player::PlayerGoalsOrder>;
}

Team::~Team()
{
    delete players;
    delete playerGoal;
}

int Team::get_num_players() const
{
    return num_players;
}

int Team::get_num_goalkeepers() const
{
    return num_goalkeepers;
}

int Team::get_ID () const
{
    return this->teamID;
}

void Team::add_points(int points_add)
{
    points += points_add;
}

void Team::add_goals_cards(int to_add)
{
    tot_goals_cards += to_add;
}

void Team::more_game_played()
{
    games_played++;
}

Player* Team::get_top_player() const
{
    return playerGoal->get_higher();
}

AVL_Tree<Player*, Player::PlayerIDOrder>* Team::get_players() const
{
    return players;
}

AVL_Tree<Player*, Player::PlayerGoalsOrder>* Team::get_playersGoals() const
{
    return playerGoal;
}

void Team::change_ID(int new_ID)
{
    teamID = new_ID;
}

void Team::remove_player(int playerID)
{
    Node<Player*,Player::PlayerIDOrder>* temp = players->search(playerID);
    if(temp== nullptr)
    {
        return;
    }
    Player* to_remove =temp->get_data_Node();
    if (!to_remove)
        return;
    num_players--;
    if (to_remove->is_goalkeeper())
        num_goalkeepers--;
    tot_goals_cards -= to_remove->get_goals();
    tot_goals_cards += to_remove->get_cards();
    players->remove(playerID);
    playerGoal->remove(to_remove);
}

void Team::add_player (Player* player)
{
    players->insert_to_tree(player);
    playerGoal->insert_to_tree(player);
    num_players++;
    if (player->is_goalkeeper())
        num_goalkeepers++;
    tot_goals_cards += player->points();
}

int Team::get_games_played() const
{
    return games_played;
}

bool Team::is_legal() const
{
    if (num_goalkeepers > 0 && num_players >= 11)
        return true;
    return false;
}

bool Team::operator >(const Team* p1) const
{
    if(p1->teamID  < this->teamID)
    {
        return true;
    }
    else
        return false;
}

int Team::tot_game_points() const
{
    return points + tot_goals_cards;
}

int Team::get_points() const
{
    return points;
}

void Team::match (int* table) const
{
    if (table[0] == 0)
    {
        table[0] = get_ID();
        table[1] = tot_game_points();
    }
    else
    {
        table[1] += tot_game_points() + 3;
        if (tot_game_points() > table[1])
        {
            table[0] = get_ID();
        }
    }
}

Team* Team::new_united_team (Team* t1, int newTeamID)
{
    Team* new_team = new Team(newTeamID, this->points + t1->points);
    new_team->num_players = this->num_players + t1->num_players;
    new_team->num_goalkeepers = this->num_goalkeepers + t1->num_goalkeepers;
    new_team->tot_goals_cards = this->tot_goals_cards + t1->tot_goals_cards;
    delete new_team->players;
    delete new_team->playerGoal;
    new_team->players = this->players->unite(t1->players);
    players->set_root();
    new_team->playerGoal = this->playerGoal->unite(t1->playerGoal);
    new_team->players->inorder_change(new_team->players->get_root(), new_team);
    this->num_players = 0;
    t1->num_players = 0;
    new_team->players->Highest_setting();
    new_team->playerGoal->Highest_setting();
    return new_team;
}

void Team::player_updated(Player* player, int gamesPlayed, int scoredGoals, int cardsReceived)
{
    playerGoal->remove(player);
    player->add_games(gamesPlayed);
    player->add_goals(scoredGoals);
    player->add_cards(cardsReceived);
    playerGoal->insert_to_tree(player);

}

bool TeamIDOrder::operator()(const Team* t1, const Team* t2) const
{
    return t1->get_ID() > t2->get_ID();
}

bool TeamIDOrder::operator()(const Team* t1, int num) const
{

    return t1->get_ID() > num;
}

bool TeamIDOrder::operator()(int num, const Team* t1) const
{

    return num > t1->get_ID();
}

