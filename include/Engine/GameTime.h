#ifndef GAMETIME_H
#define GAMETIME_H

#include "EngineExport.h"
#include "EngineTypes.hpp"
#include <SFML/System/Clock.hpp>
namespace se
{

// Controls the update cycles of a gameloop:
class SEVENGINEDLL_API GameTime
{
public:
	/* Usage in a gameloop:
	  	tick()
	  	while(readyForNextUpdate())
	  	{
	  		<clear backbuffer>
	  		<update game>
	  		<draw & display
	  		
	  		update()
	  	}
	*/ 
	GameTime();
	GameTime(int ticks_per_second, int skip_ticks, int max_frame_skips);

	bool readyForNextUpdate();

	se::uint getNextGameTick();
	se::uint getTicks();
	int getTicksPerSecond();
	int getSkipTicks();
	int getMaxFrameSkip();
	void setTicksPerSecond(int tps);
	void setSkipTicks(int st);
	void setMaxFrameSkip(int mfs);
	void tick();
	void init();
	void update();

private:
	se::uint m_ticks;
	se::uint m_next_game_tick;
	int m_ticks_per_second;
	int m_skip_ticks;
	int m_max_frame_skip;
	int m_loops;

	sf::Clock m_clock;
};
}

#endif