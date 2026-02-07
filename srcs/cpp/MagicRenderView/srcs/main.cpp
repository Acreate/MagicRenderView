#include <mainCallFunction.h>
int main( int argc, char *argv[ ], char *envp[ ] ) {
	int exec = MainCallFunction::runCode( argc, argv, envp );
	return exec;
}
