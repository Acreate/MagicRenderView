#include "nodeDirectorStack.h"

#include <qt/node/director/nodeDirector.h>

#include "../../../node/director/nodeItemInfo.h"
#include "../../../node/director/nodePortLinkInfo.h"
#include "../../../node/nodeItemMenu/nodeItemMenu.h"
#include "../../../node/prot/inputProt/nodeInputPort.h"

#include "../../../widgets/mainWidget.h"

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

	NodeItem *nodeItemPtr;
	NodeItemInfo *nodeItemInfo;
	std_vector< uint8_t > subBuff;
	size_t subCount = 0;
	for( ; nodeItemIndex < nodeItemCount; ++nodeItemIndex ) {
		nodeItemInfo = nodeItemArrayPtr[ nodeItemIndex ];
		if( nodeItemInfo == nullptr ) {
			++subCount;
			continue;
		}
		nodeItemPtr = nodeItemInfo->nodeItem;
		fillBinVector( nodeItemPtr->getMetaObjectPathName( ), buff );
		subBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->generateCode, sizeof( nodeItemPtr->generateCode ), buff );
		subBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->nodePosX, sizeof( nodeItemPtr->nodePosX ), buff );
		subBuff.append_range( buff );
		fillBinVector( &nodeItemPtr->nodePosY, sizeof( nodeItemPtr->nodePosY ), buff );
		subBuff.append_range( buff );
		nodeItemPtr->toBinData( buff );
		subBuff.append_range( buff );
	}
	nodeItemCount -= subCount;
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );
	resultBuff.append_range( subBuff );

	nodeItemCount = nodeDirector->linkVectorPairt.size( );

	nodeItemIndex = 0;
	auto nodePortLinkInfoArrayPtr = nodeDirector->linkVectorPairt.data( );
	QString linkName( "%1/%2" );

	QString nodeItemCodeName;
	size_t outPortCount;
	QString inputPortName;
	NodePortLinkInfo *nodePortLinkInfo;
	std::pair< NodeItem *, std::vector< std::pair< NodeOutputPort *, QAction * > > > *outPortArrayPtr;
	size_t outPortIndex;
	subBuff.clear( );
	for( ; nodeItemIndex < nodeItemCount; ++nodeItemIndex ) {

		nodePortLinkInfo = nodePortLinkInfoArrayPtr[ nodeItemIndex ];
		if( nodePortLinkInfo == nullptr ) {
			++subCount;
			continue;
		}
		inputPortName = linkName.arg( nodePortLinkInfo->inputPort->parentItem->generateCode ).arg( nodePortLinkInfo->inputPort->generateCode );

		fillBinVector( inputPortName, buff );
		subBuff.append_range( buff );

		outPortCount = nodePortLinkInfo->outputPorts.size( );
		fillBinVector( &outPortCount, sizeof( outPortCount ), buff );
		subBuff.append_range( buff );
		if( outPortCount == 0 )
			continue;
		outPortArrayPtr = nodePortLinkInfo->outputPorts.data( );
		outPortIndex = 0;
		for( ; outPortIndex < outPortCount; ++outPortIndex ) {
			auto &pair = outPortArrayPtr[ outPortIndex ];
			nodeItemCodeName = linkName.arg( pair.first->generateCode );
			for( auto &[ prot, action ] : pair.second ) {
				inputPortName = nodeItemCodeName.arg( prot->generateCode );
				fillBinVector( inputPortName, buff );
				subBuff.append_range( buff );
			}
		}
	}
	nodeItemCount -= subCount;
	fillBinVector( &nodeItemCount, sizeof( nodeItemCount ), buff );
	resultBuff.append_range( buff );
	resultBuff.append_range( subBuff );

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
	size_t nodeInfoCount = 0;
	count = fillObjVector( &nodeInfoCount, sizeof( nodeInfoCount ), offerPtr, mod );

	offerPtr = offerPtr + count;
	if( nodeInfoCount == 0 ) {
		result_count = offerPtr - source_data_ptr;
		return true;
	}

	mod -= count;
	typeUseCount = nodeDirector->nodeItemInfoVector.size( );
	if( typeUseCount ) {
		needCount = 0;
		auto data = nodeDirector->nodeItemInfoVector.data( );
		for( ; needCount < typeUseCount; ++needCount )
			if( data[ needCount ] != nullptr ) {
				NodeItem *nodeItem = data[ needCount ]->nodeItem;
				NodeItemInfo *nodeItemInfo = data[ needCount ];
				data[ needCount ] = nullptr;
				delete nodeItemInfo;
				delete nodeItem;
			}
		nodeDirector->nodeItemInfoVector.clear( );
	}
	nodeDirector->linkVectorPairt.clear( );

	QString nodeItemName;
	nodeDirector->nodeItemInfoVector.resize( nodeInfoCount, nullptr );
	size_t getNodeNameIndex = 0;

	QString *pointer;
	NodeItem *nodeItem;
	QStringList split;
	size_t generateCode;
	int nodePosX;
	int nodePosY;
	QPoint glpos;

	for( ; getNodeNameIndex < nodeInfoCount; ++getNodeNameIndex ) {
		count = fillObjVector( &nodeItemName, offerPtr, mod );
		if( count == 0 ) {
			QString info( "无法获取节点名称" );
			tools::debug::printError( info );
			return false;
		}
		split = nodeItemName.split( "/" );
		if( split.size( ) != 2 ) {
			QString info( "节点名称异常( %1 ) -> 无法使用 / 切分成 2 组" );
			tools::debug::printError( info.arg( nodeItemName ) );
			return false;
		}
		offerPtr = offerPtr + count;
		mod -= count;
		generateCode = 0;
		count = fillObjVector( &generateCode, sizeof( generateCode ), offerPtr, mod );
		if( count == 0 || generateCode == 0 ) {
			QString info( "节点生成代码异常 %1" );
			tools::debug::printError( info.arg( generateCode ) );
			return false;
		}
		offerPtr = offerPtr + count;
		mod -= count;

		count = fillObjVector( &nodePosX, sizeof( nodePosX ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		count = fillObjVector( &nodePosY, sizeof( nodePosY ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		glpos = QPoint( nodePosX, nodePosY );
		glpos = nodeDirector->mainWidget->mapToGlobal( glpos );
		nodeDirector->nodeItemCreateMenu->move( glpos );

		pointer = split.data( );
		nodeItem = nodeDirector->createNodeItem( pointer[ 0 ], pointer[ 1 ] );
		if( nodeItem == nullptr ) {
			QString info( "无法创建 %1 节点" );
			tools::debug::printError( info.arg( nodeItemName ) );
			return false;
		}
		nodeItem->generateCode = generateCode;
		count = nodeItem->loadBinData( offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
	}
	nodeDirector->sortNodeItemInfo( );
	// 连接数量
	count = fillObjVector( &nodeInfoCount, sizeof( nodeInfoCount ), offerPtr, mod );

	offerPtr = offerPtr + count;
	if( nodeInfoCount == 0 ) {
		result_count = offerPtr - source_data_ptr;
		return true;
	}

	mod -= count;
	getNodeNameIndex = 0;
	QString inputPortName;
	QStringList list;
	QString *stringDataPtr;
	bool converResultFlag;
	size_t inputNodeItemCode;
	size_t inputNodeItemPortCode;
	size_t outPortIndex;
	QString outputPortName;
	QStringList subList;
	QString *subStringDataPtr;
	size_t outputNodeItemCode;
	size_t outputNodeItemPortCode;
	for( ; getNodeNameIndex < nodeInfoCount; ++getNodeNameIndex ) {
		count = fillObjVector( &inputPortName, offerPtr, mod );
		list = inputPortName.split( "/" );
		if( count == 0 || list.size( ) != 2 ) {
			QString msg( "[%1]无法使用 / 切分成 2 组" );
			tools::debug::printError( msg.arg( inputPortName ) );
			return false;
		}
		stringDataPtr = list.data( );
		converResultFlag = false;
		inputNodeItemCode = stringDataPtr[ 0 ].toULongLong( &converResultFlag );
		if( converResultFlag == false ) {
			QString msg( "[%1]无法正确转换到生成节点编号" );
			tools::debug::printError( msg.arg( stringDataPtr[ 0 ] ) );
			return false;
		}
		converResultFlag = false;
		inputNodeItemPortCode = stringDataPtr[ 1 ].toULongLong( &converResultFlag );
		if( converResultFlag == false ) {
			QString msg( "[%1]无法正确转换到生成端口编号" );
			tools::debug::printError( msg.arg( stringDataPtr[ 1 ] ) );
			return false;
		}
		offerPtr = offerPtr + count;
		mod -= count;

		count = fillObjVector( &result_count, sizeof( result_count ), offerPtr, mod );
		offerPtr = offerPtr + count;
		mod -= count;
		outPortIndex = 0;
		for( ; outPortIndex < result_count; ++outPortIndex ) {

			count = fillObjVector( &outputPortName, offerPtr, mod );
			subList = outputPortName.split( "/" );
			if( count == 0 || subList.size( ) != 2 ) {
				QString msg( "[%1]无法使用 / 切分成 2 组" );
				tools::debug::printError( msg.arg( outputPortName ) );
				return false;
			}
			subStringDataPtr = subList.data( );
			converResultFlag = false;
			outputNodeItemCode = subStringDataPtr[ 0 ].toULongLong( &converResultFlag );
			if( converResultFlag == false ) {
				QString msg( "[%1]无法正确转换到生成节点编号" );
				tools::debug::printError( msg.arg( subStringDataPtr[ 0 ] ) );
				return false;
			}
			converResultFlag = false;
			outputNodeItemPortCode = subStringDataPtr[ 1 ].toULongLong( &converResultFlag );
			if( converResultFlag == false ) {
				QString msg( "[%1]无法正确转换到生成端口编号" );
				tools::debug::printError( msg.arg( subStringDataPtr[ 1 ] ) );
				return false;
			}
			if( nodeDirector->connectLink( inputNodeItemCode, inputNodeItemPortCode, outputNodeItemCode, outputNodeItemPortCode ) == false ) {
				QString msg( "[%1/%2 -> %3/%4] 无法正确连接" );
				tools::debug::printError( msg.arg( inputNodeItemCode ).arg( inputNodeItemPortCode ).arg( outputNodeItemCode ).arg( outputNodeItemPortCode ) );
				return false;
			}
			offerPtr = offerPtr + count;
			mod -= count;
		}
	}

	offerPtr = offerPtr + count;
	result_count = offerPtr - source_data_ptr;
	return true;
}
