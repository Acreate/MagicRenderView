#include "nodeDirectorStack.h"

#include <qt/node/director/nodeDirector.h>

#include "../../../node/director/nodeItemInfo.h"
#include "../../../node/director/nodePortLinkInfo.h"
#include "../../../node/prot/inputProt/nodeInputPort.h"

NodeDirectorStack::NodeDirectorStack( ) : I_Stack( typeid( t_current_type ) ) {

}
bool NodeDirectorStack::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
	if( target_type_info != stackTypeInfo )
		return false;

	std_vector< uint8_t > resultBuff;
	QString typeName = target_type_info.name( );
	fillBinVector( typeName, resultBuff );

	// 存储 nodeitem 列表

	auto nodeDirector = ( NodeDirector * ) target_ptr;
	std_vector< uint8_t > buff;
	size_t nodeItemCount = nodeDirector->generateNodeItems.size( );
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );
	auto nodeItemArrayPtr = nodeDirector->generateNodeItems.data( );
	size_t nodeItemIndex = 0;
	for( ; nodeItemIndex < nodeItemCount; ++nodeItemIndex ) {
		NodeItemInfo *nodeItemInfo = nodeItemArrayPtr[ nodeItemIndex ];
		if( nodeItemInfo == nullptr )
			continue;
		auto nodeItemPtr = nodeItemInfo->nodeItem;
		fillBinVector( nodeItemPtr->getMetaObjectPathName( ), buff );
		resultBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->generateCode, sizeof( nodeItemPtr->generateCode ), buff );
		resultBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->nodePosX, sizeof( nodeItemPtr->nodePosX ), buff );
		resultBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->nodePosY, sizeof( nodeItemPtr->nodePosY ), buff );
		resultBuff.append_range( buff );
		if( nodeItemPtr->toBinData( buff ) == 0 )
			continue;
		resultBuff.append_range( buff );
	}
	nodeItemCount = nodeDirector->linkVectorPairt.size( );
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );
	nodeItemIndex = 0;
	auto nodePortLinkInfoArrayPtr = nodeDirector->linkVectorPairt.data( );
	QString linkName( "%1/%2" );
	for( ; nodeItemIndex < nodeItemCount; ++nodeItemIndex ) {
		NodePortLinkInfo *nodePortLinkInfo = nodePortLinkInfoArrayPtr[ nodeItemIndex ];
		if( nodePortLinkInfo == nullptr )
			continue;
		QString inputPortName = linkName.arg( nodePortLinkInfo->inputPort->parentItem->generateCode ).arg( nodePortLinkInfo->inputPort->getMetaObjectPathName( ) );

		fillBinVector( inputPortName, buff );
		resultBuff.append_range( buff );

		size_t outPortCount = nodePortLinkInfo->outputPorts.size( );
		fillBinVector( &outPortCount, sizeof( outPortCount ), buff );
		resultBuff.append_range( buff );
		if( outPortCount == 0 )
			continue;
		auto outPortArrayPtr = nodePortLinkInfo->outputPorts.data( );
		for( size_t outPortIndex = 0; outPortIndex < outPortCount; ++outPortIndex ) {
			auto &pair = outPortArrayPtr[ outPortIndex ];
			QString nodeItemCodeName = linkName.arg( pair.first->generateCode );
			for( auto &[ prot, action ] : pair.second ) {
				inputPortName = nodeItemCodeName.arg( prot->getMetaObjectPathName( ) );
				fillBinVector( inputPortName, buff );
				resultBuff.append_range( buff );
			}
		}
	}

	nodeItemCount = resultBuff.size( );
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), result_vector );
	result_vector.append_range( resultBuff );
	result_count = result_vector.size( );
	return true;
}
bool NodeDirectorStack::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != stackTypeInfo )
		return false;
	size_t needCount = 0;
	size_t typeUseCount = sizeof( size_t );
	size_t count = fillObjVector( &needCount, typeUseCount, source_data_ptr, source_data_count );
	size_t mod = source_data_count - count;
	if( needCount > mod )
		return false;
	auto offerPtr = source_data_ptr + count;
	QString typeName;
	count = fillObjVector( &typeName, offerPtr, mod );
	if( typeName != stackTypeInfo.name( ) )
		return false;
	return false;
}
