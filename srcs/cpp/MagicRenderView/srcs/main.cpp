#include <mainCallFunction.h>
// 内存泄漏检查开关

// #define CRTDBG

#include <cmake_include_to_c_cpp_header_env.h>
#if Builder_Tools_MSVC
	#ifdef CRTDBG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
	#else
		#define _CrtSetReportMode(...)
		#define _CrtDumpMemoryLeaks(...)
	#endif
#endif

int main( int argc, char *argv[ ], char *envp[ ] ) {

	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );

	int exec = MainCallFunction::runCode( argc, argv, envp );

	_CrtDumpMemoryLeaks( );

	return exec;
}
