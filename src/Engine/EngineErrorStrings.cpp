#include "EngineErrorStrings.hpp"

const char* se::Error::Unknown()
{
	return "UNKNOWN_ERROR";
}

const char* se::Error::FilesMissing::Audio()
{
	return "Could not load audio: Files missing.\nPlease re-download the game";
}

const char* se::Error::FilesMissing::Font()
{
	return "Could not load font: Files missing.\nPlease re-download the game";
}

const char* se::Error::FilesMissing::Image()
{
	return "Could not load image: Files missing.\nPlease re-download the game";
}


const char* se::Error::StartUp::Initialization()
{
	return "Could not initialize on startup.";
}
