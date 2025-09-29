#include "./readFile.h"

#include "../../prot/inputProt/impInputPort/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/stringOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) );
ReadFile::ReadFile(  ) : NodeItem(  ) {
}
bool ReadFile::intPortItems( MainWidget *parent ) {
	setNodeTitleName( getMetaObjectName( ) );
	StringInputPort *inputPort = new StringInputPort( this );
	inputPort->setTitle( "文件路径" );
	appendInputProt( inputPort );
	inputPort = new StringInputPort( this );
	inputPort->setTitle( "限定目录" );
	appendInputProt( inputPort );

	
	StringOutputPort *outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件全路径" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件所在目录" );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件创建日期" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件更改日期" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件拥有者" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件基本全名称" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件基本名称" );
	appendOutputProt( outputPort );
	outputPort = new StringOutputPort( this );
	outputPort->setTitle( "文件后缀名" );
	appendOutputProt( outputPort );
	
	updateTitleLayout( );
	updateInputLayout( );
	updateOutputLayout( );
	integrateLayout( );
	return true;
}
