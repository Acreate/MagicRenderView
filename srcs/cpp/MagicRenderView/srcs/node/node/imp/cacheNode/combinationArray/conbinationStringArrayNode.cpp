#include "conbinationStringArrayNode.h"

#include <director/varDirector.h>
#include <tools/varDirectorTools.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/inputPort/cache/stringCacheInputPort.h>
#include <node/port/outputPort/anyVar/anyVarOutputPort.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

ConbinationStringArrayNode::ConbinationStringArrayNode( const QString &node_name ) : CacheNode( node_name ) {
	outVarPtr = nullptr;
}
bool ConbinationStringArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "字符串" ), cacheInputPort );
		Def_AppendInputPortType( tr( "条件" ), anyInputPort );
		Def_AppendBindVarOutputPortType( tr( "无符号整数序列" ), vectorOutPortPtr, outVarPtr );
		Def_AppendOutputPortType( tr( "条件" ), anyOutputPort );
		if( setPortMultiple( cacheInputPort, true ) == false )
			return false;
		return true;
	};
	return CacheNode::initEx( parent );
}
bool ConbinationStringArrayNode::updateLayout( ) {
	if( CacheNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ConbinationStringArrayNode::readyNodeRunData( ) {
	return true;
}

bool ConbinationStringArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

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
	QString *converPtr;
	for( index = 0; index < count; ++index ) {
		varDirector = anyOutputArrayPtr[ index ]->getVarDirector( );
		varPtr = anyOutputArrayPtr[ index ]->getVarPtr( );
		if( varDirector->cast_ptr( varPtr, converPtr ) == false )
			continue;
		outVarPtr->emplace_back( *converPtr );
	}

	return true;
}
