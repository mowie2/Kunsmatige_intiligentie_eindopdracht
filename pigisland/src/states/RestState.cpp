#include "../../include/states/RestState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <iostream>

using namespace kmint;
using namespace kmint::pigisland;
using namespace kmint::map;
RestState::RestState(kmint::pigisland::shark& shark_) : _shark(shark_)
{
}

void RestState::Update(kmint::delta_time dt)
{
	t_since_move_ += dt;



	if (to_seconds(t_since_move_) >= waiting_time(_shark.node())) {
		t_since_move_ = from_seconds(0);
		_shark.goToRestingPlace();
		auto path = _shark.get_path();
		
		if (!path.empty())
		{
			std::cout << "Moving to rest spot\n";
			_shark.node(*path[0]);
			t_since_move_ = from_seconds(0);
		}



		if (path.empty()) {
		
			restCounter++;
			std::cout << "Resting\n";
			if(restCounter >= 100)
			{
				std::cout << "Rested\n";
				_shark.stepsTaken = 0;
				restCounter = 0;
				_shark.SetState(pigisland::shark::WANDER_STATE);
			}

		}
	}
}
