#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    Teams_Players = new UF();
    TeamsByAbility = new AVL_Tree<Team*, TeamAbilityOrder>;
}

world_cup_t::~world_cup_t()
{
    TeamsByAbility->postorderDelete_data(TeamsByAbility->get_root());
    Teams_Players->pre_des();
    delete Teams_Players;
    delete TeamsByAbility;
}

StatusType world_cup_t::add_team(int teamID)
{
    if(teamID <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    else if(Teams_Players->teamExists(teamID))
    {
        return StatusType::FAILURE;
    }
    else
    {
        try
        {
            Team *team = new Team(teamID);
            Teams_Players->addTeam(team);
            TeamsByAbility->insert_to_tree(team);
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
    }
}

StatusType world_cup_t::remove_team(int teamID)
{
    if(teamID <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    else
    {
        Team *team1 = Teams_Players->get_team(teamID);
        if (!team1)
            return StatusType::FAILURE;
        else
        {
            try
            {
                Teams_Players->removeTeam(teamID);
                TeamsByAbility->remove(team1);
                delete team1;
            }
            catch (std::bad_alloc &)
            {
                return StatusType::ALLOCATION_ERROR;
            }
            return StatusType::SUCCESS;
        }
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <=0 || teamId <= 0 || gamesPlayed < 0 ||cards < 0 || !(spirit.isvalid()))
    {
        return StatusType::INVALID_INPUT;
    }
    Team* temp1 = Teams_Players->get_team( teamId);
    if(!temp1)
    {
        return StatusType::FAILURE;
    }
    if(Teams_Players->player_exists(playerId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        TeamsByAbility->remove(temp1);
        temp1->change_per(spirit);
        temp1->add_ability(ability);
        if(goalKeeper)
        {
            temp1->add_goalkeeper();
        }
        TeamsByAbility->insert_to_tree((temp1));
        permutation_t per1 = temp1->get_per();
        Player *player = new Player(playerId, gamesPlayed, ability, cards, goalKeeper, per1);
        Teams_Players->insert(player, temp1);

    }
    catch (std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2 )
    {
        return output_t<int>(StatusType::INVALID_INPUT) ;
    }
    Team* temp1 = Teams_Players->get_team( teamId1);
    Team* temp2 = Teams_Players->get_team( teamId1);
    if (temp1 == nullptr || temp2 == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    if(!(temp1->exists_goalkeeper()) || !(temp2->exists_goalkeeper()))
    {
        return output_t<int>(StatusType::FAILURE);
    }
    int team1_force = temp1->get_points() + temp1->get_ability();
    int team2_force = temp2->get_points() + temp2->get_ability();
    temp1->get_players()->player->add_games(1);
    temp2->get_players()->player->add_games(1);
    if(team1_force != team2_force)
    {
        if(team1_force > team2_force)
        {
            temp1->add_points(3);
            return output_t<int>(1);
        }
        temp2->add_points(3);
        return output_t<int>(3);
    }
    team1_force = temp1->get_per().strength();
    team2_force = temp2->get_per().strength();
    if(team1_force == team2_force)
    {
        temp1->add_points(1);
        temp2->add_points(1);
        return output_t<int>(0);
    }
    if(team1_force > team2_force)
    {
        temp1->add_points(3);
        return output_t<int>(2);
    }
    temp2->add_points(3);
    return output_t<int>(4);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    else if(!(Teams_Players->player_exists(playerId)))
    {
        return output_t<int>(StatusType::FAILURE);
    }
    Teams_Players->find(playerId);
    return output_t<int>(Teams_Players->get_sum_games(playerId));
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId <= 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    else if(!(Teams_Players->player_exists(playerId)))
    {
        return StatusType::FAILURE;
    }
    else if(!(Teams_Players->find(playerId)))
    {
        return StatusType::FAILURE;
    }
    Teams_Players->getPlayer(playerId)->add_cards(cards);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    else if(!(Teams_Players-> player_exists(playerId)))
    {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(Teams_Players->getPlayer(playerId)->get_cards());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(!Teams_Players->teamExists(teamId))
    {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(Teams_Players->get_team(teamId)->get_points());
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if (i < 0)
        return output_t<int>(StatusType::FAILURE);
    Node<Team*, TeamAbilityOrder>* node = TeamsByAbility->find_index(i + 1);
    if (!node)
        return output_t<int>(StatusType::FAILURE);
    return output_t<int>(node->get_data_Node()->get_ability());
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0)
    {
        return output_t<permutation_t>(StatusType::INVALID_INPUT);
    }
    else if(!Teams_Players->find(playerId))
    {
        return output_t<permutation_t>(StatusType::FAILURE);
    }
	return output_t<permutation_t>(Teams_Players->getPlayer(playerId)->get_per());
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    try
    {
        Team *team1 = Teams_Players->get_team(teamId1);
        Team *team2 = Teams_Players->get_team(teamId2);
        if (!team1 || !team2)
            return StatusType::FAILURE;
        UF_Node* p1 = team1->get_players();
        UF_Node* p2 = team2->get_players();
        p1->player->change_per_right(team2->get_per());
        Teams_Players->Union(p1, p2);
    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}
