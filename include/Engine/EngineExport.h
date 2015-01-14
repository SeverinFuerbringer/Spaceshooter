#define SEVENGINEAPI_EXPORT __declspec(dllexport)
#define SEVENGINEAPI_IMPORT __declspec(dllimport)

#if defined(SEVENGINE_EXPORTS)

	#define SEVENGINEDLL_API SEVENGINEAPI_EXPORT

#else
	
	#define SEVENGINEDLL_API SEVENGINEAPI_IMPORT 

#endif