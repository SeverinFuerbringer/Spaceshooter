//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	EngineErrorStrings.hpp
//////////////////////////////////////////////////

// Error strings for reporting errors.

#ifdef __cplusplus
extern "C"
{
#endif

#include "EngineExport.h"

namespace se
{
	namespace Error
	{
		SEVENGINEAPI_EXPORT extern const char* Unknown();

		namespace FilesMissing
		{
			SEVENGINEAPI_EXPORT extern const char* Audio();
			SEVENGINEAPI_EXPORT extern const char* Font();
			SEVENGINEAPI_EXPORT extern const char* Image();
		}

		namespace StartUp
		{
			SEVENGINEAPI_EXPORT extern const char* Initialization();
		}
	}
}

#ifdef __cplusplus
}
#endif