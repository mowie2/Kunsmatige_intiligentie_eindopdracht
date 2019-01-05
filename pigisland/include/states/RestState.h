#pragma once
#include "State.h"
#include "kmint/math/vector2d.hpp"

namespace kmint
{
	namespace pigisland
	{
		class pig;
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
	void newGeneration();
	int GenerationCount = 0;
	void newPig(kmint::pigisland::pig& father, kmint::pigisland::pig& mother, kmint::math::vector2d location, kmint::pigisland::pig& child);
};
