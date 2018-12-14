#include "../../include/states/AttackState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"

AttackState::AttackState(kmint::pigisland::shark& shark_) : _shark(shark_) {

}

void AttackState::Update(kmint::delta_time dt)
{
	_shark.SetState(_shark.WANDER_STATE);
}
