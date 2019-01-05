#include "kmint/main.hpp" // voor de main loop
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "kmint/pigisland/BorderMarker.hpp"
#include "kmint/random.hpp"

using namespace kmint;
math::vector2d random_island_location() {
	auto x = random_scalar(100, 175);
	auto y = random_scalar(550, 675);
	return { x, y };
}
int main() {
	ui::app app{};
  //  maak een venster aan
  ui::window window{app.create_window({1024, 768}, "hello", 0.90)};
  std::vector<kmint::pigisland::pig*> pigs;
  play::stage s{};

  auto map = pigisland::map();
  map.graph()[0].tagged(true);
  s.build_actor<play::background>(math::size(1024, 768),
                                  graphics::image{map.background_image()});
  s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
 
  for (int i = 0; i < 100; ++i) {
    auto* x = &s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f));
	pigs.push_back(x);
  }
	for(int i = 0; i <= map.size().width()/32; i++)
	{
		s.build_actor<pigisland::BorderMarker>(math::vector2d(i * 32.0f, 0));
		s.build_actor<pigisland::BorderMarker>(math::vector2d(i * 32.0f, map.size().height()));
	}
	for (int i = 0; i <= map.size().height() / 32; i++)
	{
		s.build_actor<pigisland::BorderMarker>(math::vector2d(0, i * 32.0f));
		s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() , i * 32.0f));
	}
	//pier 1
	s.build_actor<pigisland::BorderMarker>(math::vector2d(32, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(64, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(96, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(128, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(192, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(224, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(256, 32.0f));

	//pier 2
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 32, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 64, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 96, 32.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 32, 64.0f));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 32, 96.0f));

	//pier 3
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 32, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 32, map.size().height() - 160));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 64, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 96, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 96, map.size().height() - 160));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 96, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 96, map.size().height() - 224));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 128, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 160, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 160, map.size().height() - 96));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 192, map.size().height() - 96));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 160, map.size().height() - 64));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(map.size().width() - 192, map.size().height() - 32));


	s.build_actor<pigisland::BorderMarker>(math::vector2d(96, map.size().height() - 96));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(128, map.size().height() - 96));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, map.size().height() - 96));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(96, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(96, map.size().height() - 160));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(96, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(128, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(192, map.size().height() - 192));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, map.size().height() - 128));
	s.build_actor<pigisland::BorderMarker>(math::vector2d(160, map.size().height() - 160));

	s.build_actor<pigisland::shark>(map.graph(), pigs);
	s.build_actor<pigisland::boat>(map.graph());

	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};

	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls& ctl)
	{
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.

		for (ui::events::event& e : event_source)
		{
			// event heeft een methode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
		}
	});
}
