#ifdef _MSC_VER
	#define SEVENGINEAPI_EXPORT __declspec(dllexport)
	#define SEVENGINEAPI_IMPORT __declspec(dllimport)
#else
	#if __GNUC__ >= 4
		#define SEVENGINEAPI_EXPORT __attribute__ ((visibility ("default")))
		#define SEVENGINEAPI_IMPORT __attribute__ ((visibility ("default")))
	#else
		#define SEVENGINEAPI_EXPORT
		#define SEVENGINEAPI_IMPORT
		
		#ifdef _MSC_VER
			#pragma NOTE(No export option available on this platform.)
		#else
			#warning(No export option available on this platform.)
		#endif
	#endif
#endif

#if defined(SEVENGINE_EXPORTS)

	#define SEVENGINEDLL_API SEVENGINEAPI_EXPORT

#else
	
	#define SEVENGINEDLL_API SEVENGINEAPI_IMPORT 

#endif
