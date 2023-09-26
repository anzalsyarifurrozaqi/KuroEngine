// Platform detection using predefined macros
#ifdef _WIN32
	#ifdef _WIN64
		#define KURO_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif // _WIND64
#else
	#error "Unknown platform!"
#endif // _WIN32
