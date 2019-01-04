#include "../../include/states/RestState.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <iostream>

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
			std::cout << "Moving to rest spot\n";
			_shark.node(*path[0]);
			t_since_move_ = from_seconds(0);
		}



		if (path.empty()) {

			restCounter++;
			puts("Resting");
			if(restCounter >= 100)
			{
				puts("Rested");
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
	pig* production = _shark.pigs[0];
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
	while(true)
	{
		if(newGeneration.size() == 100)
		{
			break;
		}

		pig* father = selected[rand() % selected.size()];
		pig* mother = selected[rand() % selected.size()];
		pig* child = tempPigs[rand() % tempPigs.size()];
		production->newPig(*father, *mother, father->location(), *child);
		newGeneration.push_back(child);
		tempPigs.erase(std::remove(tempPigs.begin(), tempPigs.end(), child), tempPigs.end());
	}

	for (auto* pig : newGeneration)
	{
		pig->born = now();
		pig->hasDied(false);
		production->randomLocation(*pig);
	}
	_shark.pigs = newGeneration;
}
