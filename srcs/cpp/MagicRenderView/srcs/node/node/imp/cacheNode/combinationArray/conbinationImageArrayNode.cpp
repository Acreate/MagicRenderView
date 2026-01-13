#include "conbinationImageArrayNode.h"


#include <director/varDirector.h>
#include <tools/varDirectorTools.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/inputPort/cache/stringCacheInputPort.h>
#include <node/port/outputPort/anyVar/anyVarOutputPort.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

#include "../../../../port/inputPort/cache/imageCacheInputPort.h"
#include "../../../../port/outputPort/array/imageVectorOutputPort.h"
#include "../../../../port/outputPort/cache/imageCacheOutputPort.h"

ConbinationImageArrayNode::ConbinationImageArrayNode( const QString &node_name ) : CacheNode( node_name ) {
	outVarPtr = nullptr;
}
bool ConbinationImageArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "图像" ), cacheInputPort ) == false )
			return false;
		if( appendInputPortType( tr( "条件" ), anyInputPort ) == false )
			return false;
		if( appendOutputPortType( tr( "图像序列" ), vectorOutPortPtr ) == false )
			return false;
		if( appendOutputPortType( tr( "条件" ), anyOutputPort ) == false )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( vectorOutPortPtr, outVarPtr ) == false )
			return false;
		if( setPortMultiple( cacheInputPort, true ) == false )
			return false;
		return true;
	};
	return CacheNode::initEx( parent );
}
bool ConbinationImageArrayNode::updateLayout( ) {
	if( CacheNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ConbinationImageArrayNode::readyNodeRunData( ) {
	return true;
}

bool ConbinationImageArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	auto anyOutputPorts = getRefPort( anyInputPort );
	size_t count = anyOutputPorts.size( );
	if( count == 0 )
		return true;
	auto anyOutputArrayPtr = anyOutputPorts.data( );
	auto anyOutputPtr = anyOutputArrayPtr[ 0 ];
	auto varPtr = anyOutputPtr->getVarPtr( );
	VarDirector *varDirector = anyOutputPtr->getVarDirector( );
	if( VarDirectorTools::isTrue( varDirector, varPtr ) ) {
		if( getRefPortNodeVector( anyOutputPtr, adviseNextNodeVector ) == false )
			adviseNextNodeVector.clear( );
		setInfo( anyOutputPort, varDirector, varPtr );
		return true; // 指向的对象为 true，则返回 true
	}
	anyOutputPorts = getRefPort( cacheInputPort );
	count = anyOutputPorts.size( );
	if( count == 0 )
		return true;
	anyOutputArrayPtr = anyOutputPorts.data( );
	size_t index;
	QImage *converPtr;
	for( index = 0; index < count; ++index ) {
		varDirector = anyOutputArrayPtr[ index ]->getVarDirector( );
		varPtr = anyOutputArrayPtr[ index ]->getVarPtr( );
		if( varDirector->cast_ptr( varPtr, converPtr ) == false )
			continue;
		outVarPtr->emplace_back( *converPtr );
	}

	return true;
}
