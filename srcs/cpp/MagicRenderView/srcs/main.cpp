#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
#include "qt/tools/tools.h"
#include "qt/windows/mainWindow.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	auto templateVarType = VarTypeGenerate::templateVarType< QString >( nullptr );
	templateVarType->appendUnity( "8848" );

	QString *const*data = templateVarType->data< QString >( );
	QString string = *data[ 0 ];
	qDebug( ) << string;

	auto bin = templateVarType->toBin( );
	auto templateVarType2 = VarTypeGenerate::templateVarType< QString >( nullptr );
	templateVarType2->loadBin( bin );
	data = templateVarType2->data< QString >( );
	string = *data[ 0 ];
	qDebug( ) << string;

	delete templateVarType;
	delete templateVarType2;

	size_t metaInfo = VarTypeGenerate::setMetaInfo< QString >( bin );
	VarTypeGenerate::getMetaInfo( &string, bin.data( ), bin.size( ) );
	qDebug( ) << string;
	return 0;

	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
