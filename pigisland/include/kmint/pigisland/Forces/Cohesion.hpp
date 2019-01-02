#pragma once
#include "Force.hpp"
#include "kmint/play/free_roaming_actor.hpp"


class Cohesion : public Force
{
public:
	Cohesion(kmint::play::free_roaming_actor& actorIn, kmint::math::vector2d forceIn, float factorIn) : Force(actorIn, forceIn, factorIn) {}

	kmint::math::basic_vector2d<float> addForce(std::vector<kmint::play::actor*>& neighbours) override;
	std::unique_ptr<Force> clone() override;
private:

};
