#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <iostream>
#include "states/SavingPigsState.h"
#include "states/Forest.h"
#include "states/GrassIsland.h"
#include "states/GrainField.h"

namespace kmint
{
	namespace pigisland
	{
		boat::boat(map::map_graph& g)
			: play::map_bound_actor{ g, find_random_mooring_place(g) },
			drawable_{ *this, boat_image() } /*, map_{&g}*/
		{
			pierOne_ = &(find_node_of_kind(g, '1'));
			pierTwo_ = &(find_node_of_kind(g, '2'));
			pierThree_ = &(find_node_of_kind(g, '3'));

			RegisterStates();
			SetState(SAVING_PIGS_STATE);
		}

		void boat::act(delta_time dt)
		{
			t_since_move_ += dt;
			if (to_seconds(t_since_move_) >= waiting_time(node()))
			{
				currentState->Update(dt);

				//if(needsPath_)
		/*		{
					int randomInt = random_int(0, (pierOneChance_ + pierTwoChance + PierThreeChance));

					if(randomInt >= 0 && randomInt <= pierOneChance_)
					{
						chosenPier_ = pierOne_;
						repairAmount = random_int(30, 50);
						pierOneChance_ += repairAmount;
					}

					if(randomInt > pierOneChance_ && randomInt <= (pierTwoChance + pierOneChance_))
					{
						chosenPier_ = pierTwo_;
						repairAmount = random_int(20, 100);
						pierTwoChance += repairAmount;
					}

					if (randomInt > pierTwoChance && randomInt <= (PierThreeChance + pierTwoChance))
					{
						chosenPier_ = pierThree_;
						repairAmount = random_int(50, 50);
						pierTwoChance += repairAmount;
					}

					needsPath_ = false;
				}*/

				t_since_move_ = from_seconds(0);
			}
		}

		void boat::setPathTo(const kmint::map::map_node& target)
		{
			path = astar.FindShortestPath(this->node(), target);
		}
		const std::vector<const kmint::map::map_node*> boat::get_path() const {
			return this->path;
		}

		void boat::RegisterStates()
		{
			States[SAVING_PIGS_STATE] = std::make_unique<SavingPigsState>(*this);
			States[FOREST_STATE] = std::make_unique<Forest>(*this);
			States[GRAINFIELD_STATE] = std::make_unique<GrainField>(*this);
			States[GRASSISLAND_STATE] = std::make_unique<GrassIsland>(*this);
			//States[REPAIR_STATE] = std::make_unique<RepairState>(*this);

		}
		void boat::SetState(STATE_NAMES state)
		{
			currentState = States[state].get();
		}

	} // namespace pigisland
} // namespace kmint
