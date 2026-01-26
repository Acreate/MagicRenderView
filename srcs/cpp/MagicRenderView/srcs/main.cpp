#include <mainCallFunction.h>
#include <cmake_include_to_c_cpp_header_env.h>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
int main( int argc, char *argv[ ], char *envp[ ] ) {
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
	int exec = MainCallFunction::runCode( argc, argv, envp );
	//_CrtDumpMemoryLeaks( );
	return exec;
}
