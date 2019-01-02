#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/Forces/Alignment.hpp"
#include "kmint/pigisland/Forces/Cohesion.hpp"
#include "kmint/pigisland/Forces/Seperation.hpp"
#include "kmint/pigisland/Forces/ToKnabbel.hpp"
#include "kmint/pigisland/Forces/ToPorcus.hpp"
#include "kmint/pigisland/BorderMarker.hpp"
#include "kmint/pigisland/Forces/AwayFromBorder.hpp"


namespace kmint {
namespace pigisland {

namespace {

math::vector2d random_vector() {
  auto x = random_scalar(100, 175);
  auto y = random_scalar(550, 675);
  return {x, y};
}
} // namespace

pig::pig(math::vector2d location)
	: free_roaming_actor{ random_vector() }, drawable_{ *this, pig_image() }
{
	velocity = math::vector2d(1,-1);
	angle = 0;
	float random = random_scalar(0, 1);
	forces.emplace_back(std::make_unique<Alignment>(*this, velocity, random));
	random = random_scalar(0, 1);
	forces.emplace_back(std::make_unique<Cohesion>(*this, velocity, random));
	random = random_scalar(0, 1);
	forces.emplace_back(std::make_unique<Seperation>(*this, velocity, random));
	random = random_scalar(-1, 1);
	forces.emplace_back(std::make_unique<ToKnabbel>(*this, velocity, random));
	random = random_scalar(-1, 1);
	forces.emplace_back(std::make_unique<ToPorcus>(*this, velocity, random));
	forces.emplace_back(std::make_unique<AwayFromBorder>(*this, velocity, 2));
}

	pig::pig(pig& father, pig& mother, math::vector2d location)
		: free_roaming_actor{ location }, drawable_{ *this, pig_image() }
	{
		std::vector<pig*> parents;
		parents.push_back(&father);
		parents.push_back(&mother);

		velocity = math::vector2d(1, -1);
		int mutation = random_int(0, 50);
		angle = 0;
		float random = random_int(0,2);
	if(mutation == 0)
	{
		float value = random_scalar(0, 1);
		forces.emplace_back(std::make_unique<Alignment>(*this, velocity, value));
	}else
	{
		forces.emplace_back(parents[random]->forces[0]->clone());
	}
	if (mutation == 1)
	{
		float value = random_scalar(0, 1);
		forces.emplace_back(std::make_unique<Cohesion>(*this, velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		forces.emplace_back(parents[random]->forces[1]->clone());
	}
	if (mutation == 2)
	{
		float value = random_scalar(0, 1);
		forces.emplace_back(std::make_unique<Seperation>(*this, velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		forces.emplace_back(parents[random]->forces[2]->clone());
	}
	if (mutation == 3)
	{
		float value = random_scalar(-1, 1);
		forces.emplace_back(std::make_unique<ToKnabbel>(*this, velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		forces.emplace_back(parents[random]->forces[3]->clone());
	}
	if (mutation == 4)
	{
		float value = random_scalar(-1, 1);
		forces.emplace_back(std::make_unique<ToPorcus>(*this, velocity, value));
	}else
	{
		random = random_int(0, 2);
		forces.emplace_back(parents[random]->forces[4]->clone());
	}
		forces.emplace_back(parents[0]->forces[5]->clone());
	}
	

void pig::act(delta_time dt) {
  free_roaming_actor::act(dt);

  
		auto neighbours = getNeighbours();
		auto shark = getShark();
		auto boat = getBoat();
		auto walls = getWall();

		if(!neighbours.empty())
		{
			velocity += forces[0]->addForce(neighbours);
			velocity += forces[1]->addForce(neighbours);
			velocity += forces[2]->addForce(neighbours);
		}
		if(!shark.empty())
		{
			velocity += forces[3]->addForce(shark);
		}
		if(!boat.empty())
		{
			velocity += forces[4]->addForce(boat);
		}
	
	velocity += forces[5]->addForce(walls);
	velocity += calculate();
	float currentSpeed = sqrt(velocity.x() * velocity.x() + velocity.y() * velocity.y());
	velocity = normalize(velocity);
	if(currentSpeed < maxSpeed)
	{
		velocity *= currentSpeed * to_seconds(dt);

	}else
	{
		velocity *= maxSpeed;

	}
	move(velocity);
	
}

	math::vector2d pig::calculate()
	{
	
		math::vector2d circleCentre = velocity;

		circleCentre = normalize(circleCentre);
		circleCentre = circleCentre * 2;
	
		math::vector2d wobble = math::vector2d(0,-1);
		wobble = wobble * 2;
		
		angle = (rand() %  5) - 2;
		float xVal = cos(wobble.x()) * angle;
		float yVal = sin(wobble.y()) * angle;
		math::vector2d moveTo = math::vector2d(xVal, yVal);
		moveTo = moveTo + circleCentre;
	
		return moveTo;
	
	}

	std::vector<kmint::play::actor*> pig::getNeighbours()
	{
		std::vector<kmint::play::actor*> neighbours;
		for(auto neighbour = begin_perceived(); neighbour != end_perceived(); ++neighbour)
		{
			play::actor* ptr = &(*neighbour);
			if(dynamic_cast<pigisland::pig*>(ptr))
			{
				neighbours.push_back(ptr);
			}

		}
		return neighbours;
	}

	std::vector<kmint::play::actor*> pig::getShark()
	{
		std::vector<kmint::play::actor*> shark;
		for (auto neighbour = begin_perceived(); neighbour != end_perceived(); ++neighbour)
		{
			play::actor* ptr = &(*neighbour);
			if (dynamic_cast<pigisland::shark*>(ptr))
			{
				shark.push_back(ptr);
			}

		}
		return shark;
	}

	std::vector<kmint::play::actor*> pig::getWall()
	{
		std::vector<kmint::play::actor*> wall;
		for (auto neighbour = begin_perceived(); neighbour != end_perceived(); ++neighbour)
		{
			play::actor* ptr = &(*neighbour);
			if (dynamic_cast<pigisland::BorderMarker*>(ptr))
			{
				wall.push_back(ptr);
			}

		}
		return wall;
	}

	std::vector<kmint::play::actor*> pig::getBoat()
	{
		std::vector<kmint::play::actor*> boat;
		for (auto neighbour = begin_perceived(); neighbour != end_perceived(); ++neighbour)
		{
			play::actor* ptr = &(*neighbour);
			if (dynamic_cast<pigisland::boat*>(ptr))
			{
				boat.push_back(ptr);
			}

		}
		return boat;
	}
} // namespace pigisland

} // namespace kmint
