#include "../../include/states/AttackState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include <iostream>
#include "kmint/graph/graph.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/boat.hpp"

using namespace kmint;
using namespace pigisland;

AttackState::AttackState(kmint::pigisland::shark& shark_) : _shark(shark_)
{
}

void AttackState::Update(kmint::delta_time dt)
{
	t_since_move_ += dt;

	if (to_seconds(t_since_move_) >= waiting_time(_shark.node())) {
		std::cout << "Attacking\n";
		
		// Check if tired
		if (_shark.stepsTaken == 100)
		{
			_shark.SetState(_shark.REST_STATE);
			return;
		}
		// check if scared


		const kmint::map::map_node* closestNode = nullptr;

		for (auto possibleTarget = _shark.begin_perceived(); possibleTarget != _shark.end_perceived(); ++possibleTarget)
		{
			play::actor* ptr = &(*possibleTarget);
			if (dynamic_cast<pigisland::boat*>(ptr))
			{
				std::cout << "Yikes a boat!\n";
				_shark.SetState(_shark.SCARED_STATE);
				return;
			}
			if (!dynamic_cast<pigisland::pig*>(ptr))
			{
				continue;
			}

			auto& test = *possibleTarget;
			
			for(auto nodeLocation = _shark.graph().begin(); nodeLocation != _shark.graph().end(); ++nodeLocation)
			{
				if(closestNode == nullptr)
				{
					closestNode = &(*nodeLocation);
				}

				if(math::distance(closestNode->location(),test.location()) > math::distance(nodeLocation->location(),test.location()))
				{
					closestNode = &(*nodeLocation);
				}

			}
		}
		if (closestNode != nullptr)
		{
			_shark.setPathTo(*closestNode);
		}

		if(closestNode == nullptr)
		{
			_shark.SetState(shark::STATE_NAMES::WANDER_STATE);
			return;
		}

		auto path = _shark.get_path();



		if (!_shark.get_path().empty())
		{
			_shark.stepsTaken++;
			_shark.node(*_shark.get_path()[0]);
			t_since_move_ = from_seconds(0);
			std::cout << "On the move\n";
		}

		for (std::size_t i = 0; i < _shark.num_colliding_actors(); ++i) {
			auto &a = _shark.colliding_actor(i);
			const auto ppig = dynamic_cast<pig *>(&a);
			if (&a == ppig) {
				puts("killed a pig");
				ppig->hasDied(true);

			}
		}
		if (_shark.get_path().empty())
		{
			_shark.SetState(shark::STATE_NAMES::WANDER_STATE);
			return;
		}
	}
}
