#include "../../include/states/WanderState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>


using namespace kmint;
using namespace pigisland;

WanderState::WanderState(shark& shark_) : _shark(shark_)
{
}

void WanderState::Update(delta_time dt)
{

	t_since_move_ += dt;
	if (to_seconds(t_since_move_) >= waiting_time(_shark.node()))
	{
		std::cout << "Wandering\n";
		_shark.stepsTaken++;
		if (_shark.stepsTaken == 100)
		{
			_shark.SetState(_shark.REST_STATE);
			return;
		}

		for (auto possibleTarget = _shark.begin_perceived(); possibleTarget != _shark.end_perceived(); ++possibleTarget)
		{
			std::cout << "Found a pig\n";
			_shark.SetState(_shark.ATTACK_STATE);
			return;
		}
		_shark.node(random_adjacent_node(_shark.node()));
		t_since_move_ = from_seconds(0);

	}
}
