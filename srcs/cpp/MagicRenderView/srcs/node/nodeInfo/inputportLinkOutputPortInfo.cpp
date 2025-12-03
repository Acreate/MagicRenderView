#include "inputportLinkOutputPortInfo.h"

#include "../../director/varDirector.h"

#include "../node/node.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
InputportLinkOutputPortInfo::InputportLinkOutputPortInfo( InputPort *input_port ) : inputPort( input_port ) { }
bool InputportLinkOutputPortInfo::appendOutputPort( OutputPort *output_port ) {
	size_t count = outputPortVector.size( );
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == output_port )
			return true;
	outputPortVector.emplace_back( output_port );
	return true;
}
bool InputportLinkOutputPortInfo::removeOutputPort( OutputPort *output_port ) {
	size_t count = outputPortVector.size( );
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == output_port ) {
			outputPortVector.erase( outputPortVector.begin( ) + index );
			return true;
		}
	return false;
}
size_t InputportLinkOutputPortInfo::linkInputPortCount( ) const {
	return outputPortVector.size( );
}
bool InputportLinkOutputPortInfo::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	QString *stringPtr = nullptr;
	std::vector< uint8_t > unityData;
	std::vector< uint8_t > converData;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( stringPtr ) == false )
		return false;
	Node *parentNode = inputPort->parentNode;
	*uint64Ptr = ( uint64_t ) parentNode;

	if( varDirector.toVector( uint64Ptr, unityData ) == false )
		return false;

	*stringPtr = inputPort->portName;

	if( varDirector.toVector( stringPtr, converData ) == false )
		return false;
	unityData.append_range( converData );
	size_t count = outputPortVector.size( );
	*uint64Ptr = count;
	if( varDirector.toVector( uint64Ptr, converData ) == false )
		return false;
	unityData.append_range( converData );
	size_t index = 0;
	auto outputPortArrayPtr = outputPortVector.data( );
	for( ; index < count; ++index ) {
		parentNode = outputPortArrayPtr[ index ]->parentNode;
		*uint64Ptr = ( uint64_t ) parentNode;
		if( varDirector.toVector( uint64Ptr, converData ) == false )
			return false;
		unityData.append_range( converData );

		*stringPtr = inputPort->portName;
		if( varDirector.toVector( stringPtr, converData ) == false )
			return false;
		unityData.append_range( converData );
	}
	*uint64Ptr = unityData.size( );
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	result_vector_data.append_range( unityData );
	return true;
}
bool InputportLinkOutputPortInfo::toLinkMap( InputportLinkOutputPortInfoMap &result_map, size_t &user_data_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {

	uint64_t *uint64Ptr = nullptr;
	QString *stringPtr = nullptr;
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( stringPtr ) == false )
		return false;
	void *converPtr = uint64Ptr;
	if( varDirector.toVar( user_data_count, source_data_ptr, source_data_count, converPtr ) == false )
		return false;
	auto mod = source_data_count - user_data_count;
	if( mod < *uint64Ptr )
		return false; // 与描述最小所需数量不匹配
	auto offset = source_data_ptr + user_data_count;

	// 获取存储的节点地址
	if( varDirector.toVar( user_data_count, offset, mod, converPtr ) == false )
		return false;
	offset = offset + user_data_count;
	mod = mod - user_data_count;

	converPtr = stringPtr;
	if( varDirector.toVar( user_data_count, offset, mod, converPtr ) == false )
		return false;
	offset = offset + user_data_count;
	mod = mod - user_data_count;

	portInfo inputPortInfo( *uint64Ptr, *stringPtr );

	// 获取数组的输出节点的个数
	converPtr = uint64Ptr;
	if( varDirector.toVar( user_data_count, offset, mod, converPtr ) == false )
		return false;
	offset = offset + user_data_count;
	// 如果大于 0，则继续
	if( *uint64Ptr > 0 ) {
		mod = mod - user_data_count;
		std::vector< portInfo > outVector;
		outVector.resize( *uint64Ptr );
		size_t count = outVector.size( );
		auto pairArrayPtr = outVector.data( );
		size_t index = 0;
		for( ; index < count; ++index ) {
			// 节点存储地址
			converPtr = uint64Ptr;
			if( varDirector.toVar( user_data_count, offset, mod, converPtr ) == false )
				return false;
			offset = offset + user_data_count;
			mod = mod - user_data_count;
			// 端口名称
			converPtr = stringPtr;
			if( varDirector.toVar( user_data_count, offset, mod, converPtr ) == false )
				return false;
			offset = offset + user_data_count;
			mod = mod - user_data_count;
			pairArrayPtr[ index ] = portInfo( *uint64Ptr, *stringPtr );
		}
	}
	user_data_count = offset - source_data_ptr;
	return true;
}
