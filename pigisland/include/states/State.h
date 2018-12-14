#pragma once

#include"kmint/primitives.hpp"
class State
{
public:
	State() = default;
	~State() = default;

	virtual void Update(kmint::delta_time dt) = 0;

private:

};