#include "appDirector.h"

#include <qfile.h>
#include <QFileDialog>

#include "../app/application.h"
#include "../tools/path.h"
#include "nodeDirector.h"
bool AppDirector::syncProjectToFile( ) {
	QString saveTarget = currentProjectWorkPath + '/' + currentProjectName;
	QFile file( saveTarget );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Truncate ) == false )
		return false;
	std::vector< uint8_t > resultData;
	if( nodeDirector->toUint8VectorData( resultData ) == false )
		return false;
	char *data = ( char * ) resultData.data( );
	size_t writeCount = resultData.size( );
	if( file.write( data, writeCount ) == writeCount )
		return true;
	return false;
}
bool AppDirector::syncFileToProject( ) {

	return false;
}
bool AppDirector::init( ) {
	application = Application::getInstancePtr( );
	printerDirector = application->getPrinterDirector( );
	nodeDirector = application->getNodeDirector( );
	return true;
}
bool AppDirector::clearAppProjectInfo( QWidget *parent ) {
	if( nodeDirector->init( ) == false )
		return false;
	return true;
}
bool AppDirector::closeAppProject( QWidget *parent ) {
	if( nodeDirector->init( ) == false )
		return false;
	currentProjectWorkPath.clear( );
	currentProjectName.clear( );
	return true;
}
bool AppDirector::saveAppProject( QWidget *parent ) {
	if( currentProjectName.isEmpty( ) || currentProjectWorkPath.isEmpty( ) )
		return saveAsAppProject( parent );

	if( path::createDir( currentProjectWorkPath ) == false )
		return false;
	return syncProjectToFile( );
}
bool AppDirector::saveAsAppProject( QWidget *parent ) {

	auto saveFileName = QFileDialog::getSaveFileName( parent, tr( "保存项目" ), QDir::currentPath( ), tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	if( saveFileName.isEmpty( ) )
		return false;
	QFileInfo saveInfo( saveFileName );
	currentProjectWorkPath = saveInfo.dir( ).absolutePath( );
	currentProjectName = saveInfo.fileName( );
	return syncProjectToFile( );
}
bool AppDirector::updateAppProject( QWidget *parent ) {
	return false;
}
bool AppDirector::reloadAppProject( QWidget *parent ) {
	return false;
}
bool AppDirector::loadAppPorject( QWidget *parent ) {
	////nodeDirector->formUint8ArrayData(  )
	return false;
}
