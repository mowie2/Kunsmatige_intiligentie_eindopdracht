#include "../../include/states/GrainField.h"
#include "kmint/graph/graph.hpp"
#include "../../include/kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"

using namespace kmint;
GrainField::GrainField(kmint::pigisland::boat& boat_) : _boat(boat_) {

}

void GrainField::Update(kmint::delta_time dt)
{
	_boat.setPathTo(*_boat.pierThree_);
	if (!_boat.get_path().empty()) {
		auto path = _boat.get_path()[0];
		_boat.node(*path);
	}
	else {

		_boat.repairAmount = 50;
		_boat.PierThreeChance += _boat.repairAmount;
		_boat.boatDamage_ -= _boat.repairAmount;
		_boat.SetState(_boat.SAVING_PIGS_STATE);
	}

}