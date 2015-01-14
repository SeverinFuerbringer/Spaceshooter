#include "GameTime.h"

namespace se
{

// GameTime class:

GameTime::GameTime()
	: m_max_frame_skip(10), m_ticks(0), m_loops(0)
{
	m_ticks_per_second = 60; 
	m_skip_ticks = 1000 / m_ticks_per_second;
	m_next_game_tick = getTicks();
}


GameTime::GameTime(int ticks_per_second, int skip_ticks, int max_frame_skips)
	: m_ticks_per_second(ticks_per_second), m_skip_ticks(skip_ticks),
	m_max_frame_skip(max_frame_skips), m_ticks(0), m_loops(0)
{
	m_next_game_tick = getTicks();
}


bool GameTime::readyForNextUpdate()
{
	if(m_ticks > m_next_game_tick && m_loops < m_max_frame_skip)
	{
		return true;
	}
	else
	{
		return false;
	}
}


se::uint GameTime::getNextGameTick()
{
	return m_next_game_tick;
}


se::uint GameTime::getTicks()
{
	return m_ticks;
}


int GameTime::getTicksPerSecond()
{
	return m_ticks_per_second;
}


int GameTime::getSkipTicks()
{
	return m_skip_ticks;
}


int GameTime::getMaxFrameSkip()
{
	return m_max_frame_skip;
}


void GameTime::setTicksPerSecond(int tps)
{
	m_ticks_per_second = tps;
}


void GameTime::setSkipTicks(int st)
{
	m_skip_ticks = st;
}


void GameTime::setMaxFrameSkip(int mfs)
{
	m_max_frame_skip = mfs;
}


void GameTime::tick()
{
	m_loops = 0;
	m_ticks = m_clock.getElapsedTime().asMilliseconds();
}


void GameTime::update()
{
	m_next_game_tick += getSkipTicks();
	m_loops++;
}

}