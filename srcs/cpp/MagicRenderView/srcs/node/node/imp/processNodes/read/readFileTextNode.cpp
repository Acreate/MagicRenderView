#include "readFileTextNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfileinfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"
ReadFileTextNode::ReadFileTextNode( const QString &node_name ) : ProcessNode( node_name ) {
	outTextPtr = nullptr;
}
bool ReadFileTextNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "路径" ), filePathInputPort );
		Def_AppendBindVarOutputPortType( tr( "文本" ), outTextPort, outTextPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileTextNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ReadFileTextNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	auto &outputPorts = getRefPort( filePathInputPort );
	size_t count = outputPorts.size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPorts.data( );
	auto varDirector = outputPortArrayPtr[ 0 ]->getVarDirector( );
	auto varPtr = outputPortArrayPtr[ 0 ]->getVarPtr( );
	QString *resultFilePth;
	if( varDirector->cast_ptr( varPtr, resultFilePth ) == false )
		return true;
	QFileInfo redFile( *resultFilePth );
	if( redFile.exists( ) == false )
		return true;
	QFile file( redFile.absoluteFilePath( ) );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Text ) == false )
		return true;
	auto readAll = file.readAll( );
	*outTextPtr = QString::fromUtf8( readAll );
	return true;
}
