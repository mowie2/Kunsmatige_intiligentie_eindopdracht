#include "../../include/states/SavingPigsState.h"
#include "kmint/graph/graph.hpp"
#include "../../include/kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"
using namespace kmint;

SavingPigsState::SavingPigsState(kmint::pigisland::boat& boat_) : _boat(boat_) {

}

void SavingPigsState::Update(kmint::delta_time dt)
{
	_boat.boatDamage_++;
	_boat.node(kmint::pigisland::random_adjacent_node(_boat.node()));

	if (_boat.boatDamage_ == 100) {
		

		int randomInt = random_int(0, (_boat.pierOneChance_ + _boat.pierTwoChance + _boat.PierThreeChance));

		if (randomInt >= 0 && randomInt <= _boat.pierOneChance_)
		{
			_boat.SetState(_boat.GRASSISLAND_STATE);
			return;
		}

		if (randomInt > _boat.pierOneChance_ && randomInt <= (_boat.pierTwoChance + _boat.pierOneChance_))
		{
			_boat.SetState(_boat.FOREST_STATE);
			return;
		}

		if (randomInt > (_boat.pierTwoChance + _boat.pierOneChance_) && randomInt <= (_boat.PierThreeChance + _boat.pierTwoChance + _boat.pierOneChance_))
		{
			_boat.SetState(_boat.GRAINFIELD_STATE);
			return;
		}
	}
}
