#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "Astar.h"
#include <map>
#include "states/State.h"

namespace kmint
{
	namespace pigisland
	{
		class boat : public play::map_bound_actor
		{
		public:
			enum STATE_NAMES
			{
				SAVING_PIGS_STATE,
				FOREST_STATE,
				GRAINFIELD_STATE,
				GRASSISLAND_STATE
			};
			boat(map::map_graph& g);
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			scalar radius() const override { return 16.0; }
			void act(delta_time dt) override;
			void setPathTo(const kmint::map::map_node& target);
			const std::vector<const kmint::map::map_node*> boat::get_path() const;
			void SetState(STATE_NAMES state);
			int boatDamage_ = 0;
			int pierOneChance_ = 200;
			int pierTwoChance = 200;
			int PierThreeChance = 200;
			play::image_drawable drawable_;
			//[[maybe_unused]] map::map_graph *map_;
			delta_time t_since_move_{};
			map::map_node const* pierOne_;
			map::map_node const* pierTwo_;
			map::map_node const* pierThree_;

			map::map_node const* chosenPier_;

			int repairAmount = 0;


			bool needsPath_ = false;
			std::vector<const kmint::map::map_node*> path;
			Astar astar;
			State* currentState;
			void RegisterStates();
			std::map<STATE_NAMES, std::unique_ptr<State>> States;
		private:

		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
