#include "kmint/pigisland/Forces/ToPorcus.hpp"

kmint::math::basic_vector2d<float> ToPorcus::addForce(std::vector<kmint::play::actor*>& neighbours)
{
	if (!neighbours.empty())
	{
		const float xDif = neighbours[0]->location().x() - actor.location().x();
		const float yDif = neighbours[0]->location().y() - actor.heading().y();
		kmint::math::vector2d vect(xDif, yDif);
		force += vect;
		force = normalize(force);

		force *= factor;
	}

	return  force;
}

std::unique_ptr<Force> ToPorcus::clone()
{
	return std::make_unique<ToPorcus>(actor, force, factor);
}

