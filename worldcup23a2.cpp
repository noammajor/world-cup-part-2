#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    Teams_Players = new UF();
    TeamsByAbility = new AVL_Tree<Team, TeamAbilityOrder>;
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamID)
{
    if(teamID<0)
    {
        return StatusType::INVALID_INPUT;
    }
    else if(!Teams_Players->teamexists(teamID))
    {
        return StatusType::FAILURE;
    }
    else
    {
        Teams_Players->addTeam(teamID);
        TeamsByAbility->insert_to_tree(teamID);
        return StatusType::SUCCESS;
    }
}

StatusType world_cup_t::remove_team(int teamID)
{
    if(teamID < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    else if(Teams_Players->teamexists(teamID))
    {
        return StatusType::FAILURE;
    }
    else
    {
        Teams_Players->removeTeam(teamID);
        TeamsByAbility->remove(teamID);
        return StatusType::SUCCESS;
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId<=0 || teamId<=0 || gamesPlayed<0 ||cards<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!(spirit.isvalid()))
    {
        return StatusType::INVALID_INPUT;
    }
    if(Teams_Players->teamexists( teamId)== false)
    {
        return StatusType::FAILURE;
    }
    if(Teams_Players->player_exists(playerId))
    {
        return StatusType::FAILURE;
    }
    Teams_Players->get_team( teamId)->change_per( spirit);
    permutation_t temp = TeamsByAbility->search(teamId)->get_data_Node().get_per();
    Player* player=new Player(playerId,gamesPlayed,ability,cards,goalKeeper,temp);
    Teams_Players->insert(player, Teams_Players->get_team( teamId));

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
