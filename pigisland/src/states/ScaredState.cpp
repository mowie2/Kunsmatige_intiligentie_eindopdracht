#include "../../include/states/ScaredState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

using namespace kmint;
using namespace kmint::pigisland;
using namespace kmint::map;

ScaredState::ScaredState(kmint::pigisland::shark& shark_) : _shark(shark_)
{
}

void ScaredState::Update(kmint::delta_time dt)
{
	t_since_move_ += dt;
	if (to_seconds(t_since_move_) >= waiting_time(_shark.node())) {
		
		t_since_move_ = from_seconds(0);
		//puts("Im scared\n");
		_shark.stepsTaken++;
		scaredCounter++;

		if (_shark.stepsTaken >= 100)
		{
			scaredCounter = 0;
			_shark.SetState(_shark.REST_STATE);
			return;
		}

		_shark.node(random_adjacent_node(_shark.node()));
		if(scaredCounter >= 10)
		{
			
			scaredCounter = 0;
			_shark.SetState(_shark.WANDER_STATE);
			
		}
	}
}
