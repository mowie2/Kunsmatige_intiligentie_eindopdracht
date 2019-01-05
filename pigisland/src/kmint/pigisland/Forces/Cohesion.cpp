#include "kmint/pigisland/Forces/Cohesion.hpp"


kmint::math::basic_vector2d<float> Cohesion::addForce(std::vector<kmint::play::actor*>& neighbours)
{
	for (const auto neighbour : neighbours)
	{
		const float xDif = neighbour->location().x() - actor.location().x();
		const float yDif = neighbour->location().y() - actor.location().y();
		kmint::math::vector2d vect(xDif, yDif);
		force += vect;
	}
	if (!neighbours.empty())
	{
		force /= neighbours.size();
		force = normalize(force);

		force *= factor * 3;
	}

	return force;
}

std::unique_ptr<Force> Cohesion::clone()
{
	return std::make_unique<Cohesion>(actor, force, factor);
}

