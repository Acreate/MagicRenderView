#include "nodeTypeInfo.h"

#include "../../director/varDirector.h"
#include "../../menu/edit/normalNodeEditorPropertyMenu.h"
#include "../node/node.h"
#include "../port/outputPort/outputPort.h"
#include "../portType/portTypeInfo.h"
NodeTypeInfo::~NodeTypeInfo( ) {
	size_t count = portLinkInfoVector.size( );
	if( count ) {
		auto portTypeInfoArrayPtr = portLinkInfoVector.data( );
		for( size_t index = 0; index < count; ++index )
			delete portTypeInfoArrayPtr[ index ];
	}
}
bool NodeTypeInfo::load( Node *node_ptr ) {
	if( node_ptr->toUint8VectorData( nodeData ) == false )
		return false;
	auto point = node_ptr->pos( );
	posX = point.x( );
	posY = point.y( );
	nodeName = node_ptr->getVirtualNodeTypeName( );
	nodeGeneratorCode = node_ptr->generateCode;
	auto outputPortsArrayCount = node_ptr->outputPortVector.size( );
	if( outputPortsArrayCount == 0 )
		return true;
	auto outputPortsArrayPtr = node_ptr->outputPortVector.data( );
	size_t outputPortsArrayIndex = 0;
	for( ; outputPortsArrayIndex < outputPortsArrayCount; ++outputPortsArrayIndex ) {
		OutputPort *outputPort = outputPortsArrayPtr[ outputPortsArrayIndex ];
		size_t refInputCount = outputPort->refInputPortVector.size( );
		if( refInputCount == 0 )
			continue;
		auto refInputPortArrayPtr = outputPort->refInputPortVector.data( );
		size_t refInputIndex = 0;
		for( ; refInputIndex < refInputCount; ++refInputIndex ) {
			auto portInfo = new PortTypeInfo;
			if( portInfo->load( outputPort, refInputPortArrayPtr[ refInputIndex ] ) )
				portLinkInfoVector.emplace_back( portInfo );
			else {
				delete portInfo;
				return false;
			}
		}
	}
	return true;
}
QString NodeTypeInfo::toString( ) const {
	QString result( QObject::tr( "%1[%2](%3,%4)" ) );
	result = result.arg( nodeName ).arg( nodeGeneratorCode ).arg( posX ).arg( posY );
	QStringList qstringList;
	size_t count = portLinkInfoVector.size( );
	auto portTypeInfoPtr = portLinkInfoVector.data( );
	size_t index;
	QString nodeColor( QObject::tr( "L(%1/%2,%1/%2)" ) );
	if( count )
		for( index = 0; index < count; ++index ) {
			PortTypeInfo *typeInfoPtr = portTypeInfoPtr[ index ];
			qstringList.append( nodeColor.arg( typeInfoPtr->outputNodeGeneratorCode ).arg( typeInfoPtr->outputPortGeneratorCode ).arg( typeInfoPtr->inputNodeGeneratorCode ).arg( typeInfoPtr->inputPortGeneratorCode ) );
		}
	if( qstringList.length( ) )
		result += "{ " + qstringList.join( "," ) + " }";
	return result;
}
