#pragma once
#include "State.h"

namespace kmint {
	namespace pigisland {
		class shark;
	}
}

class AttackState : public State
{
public:
	AttackState() = default;
	AttackState(kmint::pigisland::shark& shark_);
	~AttackState() = default;

	void Update(kmint::delta_time dt) override;
	kmint::pigisland::shark& _shark;

private:
	kmint::delta_time t_since_move_{};
};