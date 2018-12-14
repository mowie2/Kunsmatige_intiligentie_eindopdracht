#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "../../../include/states/AttackState.h"
#include "../../../include/states/WanderState.h"
#include "../../../include/states/RestState.h"
#include "../../../include/states/ScaredState.h"

namespace kmint
{
	namespace pigisland
	{
		shark::shark(map::map_graph& g)
			: play::map_bound_actor{g, find_shark_resting_place(g)},
			  drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node())
		{
			RegisterStates();
			SetState(WANDER_STATE);
		}

		void shark::act(delta_time dt)
		{
			currentState->Update(dt);
		}


		void shark::RegisterStates()
		{
			States[ATTACK_STATE] = std::make_unique<AttackState>(*this);
			States[WANDER_STATE] = std::make_unique<WanderState>(*this);
			States[REST_STATE] = std::make_unique<RestState>(*this);
			States[SCARED_STATE] = std::make_unique<ScaredState>(*this);
		}

		void shark::SetState(STATE_NAMES state)
		{
			currentState = States[state].get();
		}
	} // namespace pigisland
} // namespace kmint
