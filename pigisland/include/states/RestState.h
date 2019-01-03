#pragma once
#include "State.h"

namespace kmint
{
	namespace pigisland
	{
		class shark;
	}
}

class RestState : public State
{
public:
	RestState() = default;
	RestState(kmint::pigisland::shark& shark_);
	~RestState() = default;

	void Update(kmint::delta_time dt) override;
	kmint::pigisland::shark& _shark;

private:
	kmint::delta_time t_since_move_{};
	int restCounter = 0;
};
