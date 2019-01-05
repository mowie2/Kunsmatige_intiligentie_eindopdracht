#include "../../include/states/RestState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <iostream>
#include "kmint/random.hpp"
#include "kmint/pigisland/Forces/Alignment.hpp"
#include "kmint/pigisland/Forces/Cohesion.hpp"
#include "kmint/pigisland/Forces/Seperation.hpp"
#include "kmint/pigisland/Forces/ToKnabbel.hpp"
#include "kmint/pigisland/Forces/ToPorcus.hpp"

using namespace kmint;
using namespace kmint::pigisland;
using namespace kmint::map;
RestState::RestState(kmint::pigisland::shark& shark_) : _shark(shark_)
{
}

void RestState::Update(kmint::delta_time dt)
{
	t_since_move_ += dt;



	if (to_seconds(t_since_move_) >= waiting_time(_shark.node())) {
		t_since_move_ = from_seconds(0);
		_shark.goToRestingPlace();
		auto path = _shark.get_path();

		if (!path.empty())
		{
			//std::cout << "Moving to rest spot\n";
			_shark.node(*path[0]);
			t_since_move_ = from_seconds(0);
		}



		if (path.empty()) {

			restCounter++;
			//puts("Resting");
			if (restCounter >= 1)
			{
				//puts("Rested");
				_shark.stepsTaken = 0;
				restCounter = 0;
				newGeneration();
				_shark.SetState(pigisland::shark::WANDER_STATE);
			}

		}
	}
}

void RestState::newGeneration()
{

	std::vector<kmint::pigisland::pig*> selected;
	std::vector<kmint::pigisland::pig*> tempPigs = _shark.pigs;
	//pig production = pig(math::vector2d(1, 1));
	//production.hasDied(true);
	std::vector<kmint::pigisland::pig*> newGeneration;
	for each (auto* pig in tempPigs)
	{
		if (pig->alive) {
			pig->death = now();
		}
	}

	while (true) {
		if (selected.size() == 50) {
			break;
		}
		pig* tempPig = nullptr;
		for each (auto* pig in tempPigs)
		{
			if (tempPig == nullptr) {
				tempPig = pig;
			}

			if (tempPig != pig) {

				std::chrono::duration<double> p1 = tempPig->death - tempPig->born;
				std::chrono::duration<double> p2 = pig->death - pig->born;
				if (p1.count() <= p2.count()) {
					if (tempPig != pig)
					{
						tempPig = pig;
					}

				}
			}
		}
		if (std::find(selected.begin(), selected.end(), tempPig) != selected.end()) {
			/* v contains x */
		}
		else {
			/* v does not contain x */
			selected.push_back(tempPig);
			tempPigs.erase(std::remove(tempPigs.begin(), tempPigs.end(), tempPig), tempPigs.end());
		}

	}
	newGeneration = selected;
	while (true)
	{
		if (newGeneration.size() == 100)
		{
			break;
		}

		pig* father = selected[rand() % selected.size()];
		pig* mother = selected[rand() % selected.size()];

		if(father == mother)
		{
			continue;
		}
		pig* child = tempPigs[rand() % tempPigs.size()];
		newPig(*father, *mother, father->location(), *child);
		newGeneration.push_back(child);
		tempPigs.erase(std::remove(tempPigs.begin(), tempPigs.end(), child), tempPigs.end());
	}

	for (auto* pig : newGeneration)
	{
		pig->born = now();
		
		pig->hasDied(false);
		pig->randomLocation(*pig);
	}
	_shark.pigs = newGeneration;
	float f0 = 0;
	float f1 = 0;
	float f2 = 0;
	float f3 = 0;
	float f4 = 0;
	for (auto* pig : newGeneration)
	{
		f0 += (pig->forces[0]->Factor() / 100);
		f1 += (pig->forces[1]->Factor() / 100);
		f2 += (pig->forces[2]->Factor() / 100);
		f3 += (pig->forces[3]->Factor() / 100);
		f4 += (pig->forces[4]->Factor() / 100);
	}
	GenerationCount++;
	std::cout << "==================================================\n";
	std::cout << "Generation: " << GenerationCount << "\n";
	std::cout << "Alignment: " << f0 << "\n";
	std::cout << "Cohesion: " << f1 << "\n";
	std::cout << "Seperation: " << f2 << "\n";
	std::cout << "ToKnabble: " << f3 << "\n";
	std::cout << "ToPorcus: " << f4 << "\n";
	std::cout << "==================================================\n";
}
void RestState::newPig(pig& father, pig& mother, math::vector2d location, pig& child)
{
	std::vector<pig*> parents;
	parents.push_back(&father);
	parents.push_back(&mother);

	//child.forces.clear();
	child.velocity = math::vector2d(random_scalar(-1, 1), random_scalar(-1, 1));
	int mutation = random_int(0, 50);
	child.angle = 0;
	float random = random_int(0, 2);
	if (mutation == 0)
	{
		float value = random_scalar(0, 1);
		child.forces[0] = (std::make_unique<Alignment>(child, child.velocity, value));
	}
	else
	{
		child.forces[0] = (parents[random]->forces[0]->clone());
	}
	if (mutation == 1)
	{
		float value = random_scalar(0, 1);
		child.forces[1] = (std::make_unique<Cohesion>(child, child.velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		child.forces[1] = (parents[random]->forces[1]->clone());
	}
	if (mutation == 2)
	{
		float value = random_scalar(0, 1);
		child.forces[2] = (std::make_unique<Seperation>(child, child.velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		child.forces[2] = (parents[random]->forces[2]->clone());
	}
	if (mutation == 3)
	{
		float value = random_scalar(-1, 1);
		child.forces[3] = (std::make_unique<ToKnabbel>(child, child.velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		child.forces[3] = (parents[random]->forces[3]->clone());
	}
	if (mutation == 4)
	{
		float value = random_scalar(-1, 1);
		child.forces[4] = (std::make_unique<ToPorcus>(child, child.velocity, value));
	}
	else
	{
		random = random_int(0, 2);
		child.forces[4] = (parents[random]->forces[4]->clone());
	}
	child.forces[5] = (parents[0]->forces[5]->clone());
}