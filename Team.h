#ifndef TEAM_H
#define TEAM_H

#include "AVL_tree.h"
#include "Player.h"

template<class T, class Cond>
class AVL_Tree;

class Team
{
    int teamID;
    int points;
    int num_players;
    int num_goalkeepers;
    int tot_goals_cards;
    int games_played;
    AVL_Tree<Player*, Player::PlayerIDOrder>* players;
    AVL_Tree<Player*, Player::PlayerGoalsOrder>* playerGoal;

public:
    Team(int ID, int points);

    Team& operator=(const Team&) = delete;

    Team(const Team&) = delete;

    ~Team();

    int get_ID () const;

    void remove_player(int playerID);

    void add_player (Player* player);

    int get_games_played() const;

    bool is_legal() const;

    bool operator >(const Team* p1) const;

    int tot_game_points() const;

    int get_points() const;

    void add_points(int pointsadd);

    int get_num_players() const;

    int get_num_goalkeepers() const;

    void add_goals_cards(int to_add);

    void more_game_played();

    Player* get_top_player() const;

    AVL_Tree<Player*, Player::PlayerIDOrder>* get_players() const;

    AVL_Tree<Player*, Player::PlayerGoalsOrder>* get_playersGoals() const;

    void change_ID(int new_ID);

    void match (int* table) const;

    Team* new_united_team (Team* t1, int newTeamID);

    void player_updated(Player* player, int gamesPlayed, int scoredGoals, int cardsReceived);


};

class TeamIDOrder
{
public:
    bool operator()(const Team* t1, const Team* t2) const;
    bool operator()(const Team* t1, int num) const;
    bool operator()(int num, const Team* t1) const;

};


#endif //TEAM_H
