#include "qt/application/application.h"
#include "qt/functionDeclaration/baseArithmetic/addFunctionDeclaration.h"
#include "qt/mainWindow/mainWindow.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	AddFunctionDeclaration addFunction;
	qDebug( ) << addFunction.getReturnType( ) << "=========";
	qDebug( ) << addFunction.getDeclarationName( ) << "=========";
	qDebug( ) << addFunction.getAttribute( ) << "=========";
	qDebug( ) << addFunction.getFunctionDeclarationName( ) << "=========";
	auto paramInfos = addFunction.getParamInfos( );
	for( auto paramInfo : paramInfos )
		qDebug( ) << paramInfo.get(  )->first << " : " << paramInfo.get(  )->second << "=========";

	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}
