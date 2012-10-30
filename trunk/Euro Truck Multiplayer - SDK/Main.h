/*************************************
 **
 ** You module name for ETS
 **
 ************************************/
#ifdef WIN32
	#define EXPORT extern "C" __declspec(dllexport)
#else
	#define EXPORT extern "C"
#endif