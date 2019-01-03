#pragma once
#include "State.h"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/State.h"
#include <map>

namespace kmint
{
	namespace pigisland
	{
		class shark;
	}
}

class ScaredState : public State
{
public:
	ScaredState() = default;
	ScaredState(kmint::pigisland::shark& shark_);
	~ScaredState() = default;

	void Update(kmint::delta_time dt) override;
	kmint::pigisland::shark& _shark;

private:
	kmint::delta_time t_since_move_{};
	int scaredCounter = 0;
};
