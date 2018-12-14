#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "../../../include/states/AttackState.h"
#include "../../../include/states/WanderState.h"
#include "../../../include/states/RestState.h"
#include "../../../include/states/ScaredState.h"

namespace kmint {
	namespace pigisland {

		shark::shark(kmint::map::map_graph &g)
			: play::map_bound_actor{ g, find_shark_resting_place(g) },
			drawable_{ *this, shark_image() }, map_{ &g }, resting_place_(&node()) {
			RegisterStates();
			SetState(shark::STATE_NAMES::WANDER_STATE);
		}

		void shark::act(delta_time dt) {
			currentState->Update(dt);
		}


		void shark::RegisterStates() {
			States[shark::STATE_NAMES::ATTACK_STATE] = std::make_unique<AttackState>(*this);
			States[shark::STATE_NAMES::WANDER_STATE] = std::make_unique<WanderState>(*this);
			States[shark::STATE_NAMES::REST_STATE] = std::make_unique<RestState>(*this);
			States[shark::STATE_NAMES::SCARED_STATE] = std::make_unique<ScaredState>(*this);

		}

		void shark::SetState(shark::STATE_NAMES state) {
			currentState = States[state].get();
		}
	} // namespace pigisland
} // namespace kmint
