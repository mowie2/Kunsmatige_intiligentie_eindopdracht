#include "../../include/states/Forest.h"
#include "kmint/graph/graph.hpp"
#include "../../include/kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"

using namespace kmint;
Forest::Forest(kmint::pigisland::boat& boat_) : _boat(boat_) {

}

void Forest::Update(kmint::delta_time dt)
{
	_boat.setPathTo(*_boat.pierTwo_);
	if (!_boat.get_path().empty()) {
		auto path = _boat.get_path()[0];
		_boat.node(*path);
	}
	else {

		_boat.repairAmount = random_int(20, 100);
		_boat.pierTwoChance += _boat.repairAmount;
		_boat.boatDamage_ -= _boat.repairAmount;
		_boat.SetState(_boat.SAVING_PIGS_STATE);
	}

}