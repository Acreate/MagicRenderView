#include "./readFile.h"

#include "../../prot/inputProt/impInputPort/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/stringOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) )
ReadFile::ReadFile( NodeItem_ParentPtr_Type *parent ) : NodeItem( parent ) {
	nodeTitleName = getMetaObjectName( );
	StringInputPort *inputPort = new StringInputPort( this );
	StringOutputPort *outputPort = new StringOutputPort( this );
	appendInputProt( inputPort );
	appendOutputProt( outputPort );
	inputPort->updateProtLayout( );
	outputPort->updateProtLayout( );
}
