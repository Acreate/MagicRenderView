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
	size_t nodeItemCount = nodeDirector->nodeItemInfoVector.size( );
	auto nodeItemArrayPtr = nodeDirector->nodeItemInfoVector.data( );
	size_t nodeItemIndex = 0;

	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );

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
		nodeItemPtr->toBinData( buff );
		resultBuff.append_range( buff );
	}

	nodeItemCount = nodeDirector->linkVectorPairt.size( );

	nodeItemIndex = 0;
	auto nodePortLinkInfoArrayPtr = nodeDirector->linkVectorPairt.data( );
	QString linkName( "%1/%2" );
	std_vector< uint8_t > linkVectorPairtBuff;
	size_t subCount = 0;
	for( ; nodeItemIndex < nodeItemCount; ++nodeItemIndex ) {
		NodePortLinkInfo *nodePortLinkInfo = nodePortLinkInfoArrayPtr[ nodeItemIndex ];
		if( nodePortLinkInfo == nullptr ) {
			++subCount;
			continue;
		}
		QString inputPortName = linkName.arg( nodePortLinkInfo->inputPort->parentItem->generateCode ).arg( nodePortLinkInfo->inputPort->generateCode );

		fillBinVector( inputPortName, buff );
		linkVectorPairtBuff.append_range( buff );

		size_t outPortCount = nodePortLinkInfo->outputPorts.size( );
		fillBinVector( &outPortCount, sizeof( outPortCount ), buff );
		linkVectorPairtBuff.append_range( buff );
		if( outPortCount == 0 )
			continue;
		auto outPortArrayPtr = nodePortLinkInfo->outputPorts.data( );
		for( size_t outPortIndex = 0; outPortIndex < outPortCount; ++outPortIndex ) {
			auto &pair = outPortArrayPtr[ outPortIndex ];
			QString nodeItemCodeName = linkName.arg( pair.first->generateCode );
			for( auto &[ prot, action ] : pair.second ) {
				inputPortName = nodeItemCodeName.arg( prot->generateCode );
				fillBinVector( inputPortName, buff );
				linkVectorPairtBuff.append_range( buff );
			}
		}
	}
	nodeItemCount -= subCount;
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );
	resultBuff.append_range( linkVectorPairtBuff );

	nodeItemCount = resultBuff.size( );
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), result_vector );
	result_vector.append_range( resultBuff );
	result_count = result_vector.size( );
	return true;
}
bool NodeDirectorStack::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != stackTypeInfo )
		return false;
	if( source_data_count == 0 || source_data_ptr == nullptr )
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
	offerPtr = offerPtr + count;
	mod -= count;
	auto nodeDirector = ( NodeDirector * ) target_ptr;
	if( nodeDirector->mainWidget == nullptr ) {
		tools::debug::printError( "不存在用于节点的主窗口，请使用 bool NodeDirector::setContentWidget( MainWidget *main_widget ) 配置该对象实例" );
		return false;
	}
	size_t generateCount = 0;
	count = fillObjVector( &generateCount, sizeof( generateCount ), offerPtr, mod );

	offerPtr = offerPtr + count;
	if( generateCount == 0 ) {
		result_count = offerPtr - source_data_ptr;
		return true;
	}

	mod -= count;

	nodeDirector->nodeItemInfoVector.clear( );
	nodeDirector->linkVectorPairt.clear( );

	QString nodeItemName;
	nodeDirector->nodeItemInfoVector.resize( generateCount, nullptr );
	size_t getNodeNameIndex = 0;
	while( getNodeNameIndex < generateCount ) {
		count = fillObjVector( &nodeItemName, offerPtr, mod );
		if( count == 0 ) {
			QString info( "无法获取节点名称" );
			tools::debug::printError( info );
			return false;
		}
		auto split = nodeItemName.split( "/" );
		if( split.size( ) != 2 ) {
			QString info( "节点名称异常( %1 ) -> 无法使用 / 切分成 2 组" );
			tools::debug::printError( info.arg( nodeItemName ) );
			return false;
		}
		auto pointer = split.data( );
		auto nodeItem = nodeDirector->createNodeItem( pointer[ 0 ], pointer[ 1 ] );
		if( nodeItem == nullptr ) {
			QString info( "无法创建 %1 节点" );
			tools::debug::printError( info.arg( nodeItemName ) );
			return false;
		}
		offerPtr = offerPtr + count;
		mod -= count;
		count = fillObjVector( &nodeItem->generateCode, sizeof( nodeItem->generateCode ), offerPtr, mod );

		offerPtr = offerPtr + count;
		mod -= count;
		count = fillObjVector( &nodeItem->nodePosX, sizeof( nodeItem->nodePosX ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		count = fillObjVector( &nodeItem->nodePosY, sizeof( nodeItem->nodePosY ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		count = nodeItem->loadBinData( offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;

		++getNodeNameIndex;
	}
	nodeDirector->sortNodeItemInfo( );
	// 连接数量
	count = fillObjVector( &generateCount, sizeof( generateCount ), offerPtr, mod );

	offerPtr = offerPtr + count;
	if( generateCount == 0 ) {
		result_count = offerPtr - source_data_ptr;
		return true;
	}

	mod -= count;
	std_vector_pairt< QString, std_vector< QString > > linkInfo( generateCount );
	auto data = linkInfo.data( );
	QString linkName( "%1/%2" );
	getNodeNameIndex = 0;
	for( ; getNodeNameIndex < generateCount; ++getNodeNameIndex ) {

		QString inputPortName;
		std_vector< QString > outTarget;
		count = fillObjVector( &inputPortName, offerPtr, mod );

		auto list = inputPortName.split( "/" );
		if( list.size( ) != 2 ) {
			QString msg( "[%1]无法使用 / 切分成 2 组" );
			tools::debug::printError( msg.arg( inputPortName ) );
			return false;
		}
		auto stringDataPtr = list.data( );
		bool converResultFlag = false;
		size_t inputNodeItemCode = stringDataPtr[ 0 ].toULongLong( &converResultFlag );
		if( converResultFlag == false ) {
			QString msg( "[%1]无法正确转换到生成节点编号" );
			tools::debug::printError( msg.arg( stringDataPtr[ 0 ] ) );
			return false;
		}
		converResultFlag = false;
		size_t inputNodeItemPortCode = stringDataPtr[ 0 ].toULongLong( &converResultFlag );
		if( converResultFlag == false ) {
			QString msg( "[%1]无法正确转换到生成端口编号" );
			tools::debug::printError( msg.arg( stringDataPtr[ 0 ] ) );
			return false;
		}
		offerPtr = offerPtr + count;
		mod -= count;

		count = fillObjVector( &result_count, sizeof( result_count ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		for( size_t outPortIndex = 0; outPortIndex < result_count; ++outPortIndex ) {
			QString outputPortName;
			count = fillObjVector( &outputPortName, offerPtr, mod );
			auto subList = outputPortName.split( "/" );
			if( subList.size( ) != 2 ) {
				QString msg( "[%1]无法使用 / 切分成 2 组" );
				tools::debug::printError( msg.arg( outputPortName ) );
				return false;
			}
			auto subStringDataPtr = subList.data( );
			converResultFlag = false;
			size_t outputNodeItemCode = subStringDataPtr[ 0 ].toULongLong( &converResultFlag );
			if( converResultFlag == false ) {
				QString msg( "[%1]无法正确转换到生成节点编号" );
				tools::debug::printError( msg.arg( subStringDataPtr[ 0 ] ) );
				return false;
			}
			converResultFlag = false;
			size_t outputNodeItemPortCode = subStringDataPtr[ 0 ].toULongLong( &converResultFlag );
			if( converResultFlag == false ) {
				QString msg( "[%1]无法正确转换到生成端口编号" );
				tools::debug::printError( msg.arg( subStringDataPtr[ 0 ] ) );
				return false;
			}
			if( nodeDirector->connectLink( inputNodeItemCode, inputNodeItemPortCode, outputNodeItemCode, outputNodeItemPortCode ) == false ) {
				QString msg( "[%1/%2 -> %3/%4] 无法正确连接" );
				tools::debug::printError( msg.arg( inputNodeItemCode ).arg( inputNodeItemPortCode ).arg( outputNodeItemCode ).arg( outputNodeItemPortCode ) );
				return false;
			}
			offerPtr = offerPtr + count;
			mod -= count;
			outTarget.emplace_back( outputPortName );
		}
		data[ getNodeNameIndex ] = std_pairt( inputPortName, outTarget );
	}

	offerPtr = offerPtr + count;
	result_count = offerPtr - source_data_ptr;
	return true;
}
