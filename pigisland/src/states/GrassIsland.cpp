#include "../../include/states/GrassIsland.h"
#include "kmint/graph/graph.hpp"
#include "../../include/kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"

using namespace kmint;
GrassIsland::GrassIsland(kmint::pigisland::boat& boat_) : _boat(boat_) {

}

void GrassIsland::Update(kmint::delta_time dt)
{
	_boat.setPathTo(*_boat.pierOne_);
	if (!_boat.get_path().empty()) {
		auto path = _boat.get_path()[0];
		_boat.node(*path);
	}
	else {
		
		_boat.repairAmount = random_int(30, 50); 
		_boat.pierOneChance_ += _boat.repairAmount;
		_boat.boatDamage_ -= _boat.repairAmount;
		_boat.SetState(_boat.SAVING_PIGS_STATE);
	}
	
}