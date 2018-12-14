#include "../../include/states/WanderState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"


using namespace kmint;
using namespace kmint::pigisland;

WanderState::WanderState(kmint::pigisland::shark& shark_) : _shark(shark_) {

}

void WanderState::Update(kmint::delta_time dt)
{
	t_since_move_ += dt;
	if (kmint::to_seconds(t_since_move_) >= waiting_time(_shark.node())) {

		_shark.node(random_adjacent_node(_shark.node()));
		t_since_move_ = from_seconds(0);
		_shark.SetState(_shark.ATTACK_STATE);
	}
}
