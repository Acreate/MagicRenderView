#include "./readFile.h"

#include "../../prot/inputProt/impInputPort/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/stringOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) );
ReadFile::ReadFile( NodeItem_ParentPtr_Type *parent ) : NodeItem( parent ) {
}
bool ReadFile::intPortItems( ) {
	setNodeTitleName( getMetaObjectName( ) );
	StringInputPort *inputPort = new StringInputPort( this );
	StringOutputPort *outputPort = new StringOutputPort( this );
	appendInputProt( inputPort );
	appendOutputProt( outputPort );
	updateTitleLayout( );
	updateInputLayout( );
	updateOutputLayout( );
	integrateLayout( );
	return true;
}
