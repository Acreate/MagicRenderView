#include "nodeItemInfo.h"

#include <qt/node/item/nodeItem.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>

#include "../../tools/tools.h"
NodeItemInfo::NodeItemInfo( NodeItem *node_item ) : QObject( nullptr ),
	nodeItem( node_item ) {
	manageMenu = new QMenu;
	QString title( "删除[ %1 ]节点" );
	auto addAction = manageMenu->addAction( title.arg( node_item->getMetaObjectPathName( ) ) );
	connect( addAction, &QAction::triggered, [this]( ) {
		nodeItem->deleteLater( );
	} );
}
NodeItemInfo::~NodeItemInfo( ) {
	emit releaseThisPtr( this );
	delete manageMenu;
}
bool NodeItemInfo::appendOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) {
	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == output_ref_ptr->nodeItem )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = output_ref_ptr;
				emit nodeItemInfoRefChangeOutputNodeItem( this );
				return true;
			}
	}
	emit nodeItemInfoRefChangeOutputNodeItem( this );
	outputNodeItemVector.emplace_back( output_ref_ptr );
	return true;
}
bool NodeItemInfo::removeOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) {

	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == output_ref_ptr->nodeItem ) {
				data[ index ] = nullptr;
				emit nodeItemInfoRefChangeOutputNodeItem( this );
				return true;
			}
	}
	return false;
}
bool NodeItemInfo::inOutputNodeItemInfo( NodeItem *output_ref_ptr ) const {

	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		using buffVector = decltype(outputNodeItemVector);
		buffVector subVector, subBufferVector;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr )
				if( data[ index ]->nodeItem == output_ref_ptr )
					return true;
				else
					subVector.append_range( data[ index ]->outputNodeItemVector );
		do {
			count = subVector.size( );
			if( count == 0 )
				return false;
			data = subVector.data( );
			index = 0;
			for( ; index < count; ++index )
				if( data[ index ] != nullptr )
					if( data[ index ]->nodeItem == output_ref_ptr )
						return true;
					else
						subBufferVector.append_range( data[ index ]->outputNodeItemVector );
			subVector = subBufferVector;
		} while( true );

	}
	return false;

}
bool NodeItemInfo::inOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) const {
	return inOutputNodeItemInfo( output_ref_ptr->nodeItem );
}
bool NodeItemInfo::appendInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr )
				if( data[ index ]->nodeItem == input_ref_ptr->nodeItem )
					return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = input_ref_ptr;
				emit nodeItemInfoRefChangeInputNodeItem( this );
				return true;
			}
	}
	emit nodeItemInfoRefChangeInputNodeItem( this );
	inputNodeItemInfoVector.emplace_back( input_ref_ptr );
	return true;
}
bool NodeItemInfo::removeInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr )
				if( data[ index ]->nodeItem == input_ref_ptr->nodeItem ) {
					data[ index ] = nullptr;
					emit nodeItemInfoRefChangeInputNodeItem( this );
					return true;
				}
	}
	return false;
}
bool NodeItemInfo::inInputNodeItemInfo( NodeItem *input_ref_ptr ) const {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		using buffVector = decltype(inputNodeItemInfoVector);
		buffVector subVector, subBufferVector;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr )
				if( data[ index ]->nodeItem == input_ref_ptr )
					return true;
				else
					subVector.append_range( data[ index ]->inputNodeItemInfoVector );
		do {
			count = subVector.size( );
			if( count == 0 )
				return false;
			data = subVector.data( );
			index = 0;
			subBufferVector.clear( );
			for( ; index < count; ++index )
				if( data[ index ] != nullptr )
					if( data[ index ]->nodeItem == input_ref_ptr )
						return true;
					else
						subBufferVector.append_range( data[ index ]->inputNodeItemInfoVector );
			subVector = subBufferVector;
		} while( true );

	}
	return false;
}
bool NodeItemInfo::inInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) const {
	return inInputNodeItemInfo( input_ref_ptr->nodeItem );
}
bool NodeItemInfo::getNodeItemType( nodeItemEnum::Node_Item_Type &result ) {
	result = nodeItem->getNodeMetaType( );
	return true;
}
void NodeItemInfoVector::moveNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_source_point, const size_t &inster_node_item_info_target_point ) {
	if( node_item_info_array_ptr == nullptr || inster_node_item_info_target_point == inster_node_item_info_source_point )
		return;
	size_t index = inster_node_item_info_source_point;
	auto nodeItemInfo = node_item_info_array_ptr[ index ];
	if( inster_node_item_info_target_point < inster_node_item_info_source_point )
		// 数据后移
		for( ; index > inster_node_item_info_target_point; --index )
			node_item_info_array_ptr[ index ] = node_item_info_array_ptr[ index - 1 ];
	else
		// 数据前移
		for( ; index < inster_node_item_info_target_point; ++index )
			node_item_info_array_ptr[ index ] = node_item_info_array_ptr[ index + 1 ];
	node_item_info_array_ptr[ index ] = nodeItemInfo;
}
QString NodeItemInfoVector::formatNodeInfoPath( const NodeItemInfo *const*node_item_info, const size_t &count, const QString &join_string ) {
	QStringList out;
	QString formatString( "%1(%2)" );
	for( size_t index = 0; index < count; ++index )
		out.append( formatString.arg( node_item_info[ index ]->getNodeItem( )->getMetaObjectPathName( ) ).arg( node_item_info[ index ]->getNodeItem( )->getGenerateCode( ) ) );
	return out.join( join_string );
}
size_t NodeItemInfoVector::fillNodeItemInfoVector( NodeItemInfo **source_node_item_info_array_ptr, const size_t &source_node_item_info_array_count, NodeItemInfo **target_node_item_info_array_ptr, const size_t &target_node_item_info_array_count, const std_function< bool( NodeItemInfo *check ) > &fill_check_function ) {
	size_t fillCount = 0;
	for( size_t sourceIndex = 0; sourceIndex < source_node_item_info_array_count; ++sourceIndex )
		if( fillCount == target_node_item_info_array_count )
			return fillCount;
		else if( fill_check_function( source_node_item_info_array_ptr[ sourceIndex ] ) )
			target_node_item_info_array_ptr[ fillCount++ ] = source_node_item_info_array_ptr[ sourceIndex ];
	return fillCount;
}
bool NodeItemInfoVector::builderNodeItemVector( const std_vector< NodeItemInfo * > &start_node_item_info_vector, std_vector< NodeItemInfo * > &result_run_node_item_info_vector, const NodeItemInfo *&result_first_error_node_item_info_ptr ) {
	result_first_error_node_item_info_ptr = nullptr;
	auto currentVectorCount = start_node_item_info_vector.size( );
	if( currentVectorCount == 0 )
		return false;
	result_run_node_item_info_vector.clear( );
	auto startNodeItemInfoArrayPtr = start_node_item_info_vector.data( );
	std_vector< NodeItemInfo * > resultOutNodeItemInfoPtr;
	size_t currentVectorIndex = 0;
	for( ; currentVectorIndex < currentVectorCount; ++currentVectorIndex )
		if( startNodeItemInfoArrayPtr[ currentVectorIndex ] != nullptr && fillOutputNodeItemAtVector( startNodeItemInfoArrayPtr[ currentVectorIndex ], resultOutNodeItemInfoPtr ) == true ) {
			result_run_node_item_info_vector.append_range( resultOutNodeItemInfoPtr );
			resultOutNodeItemInfoPtr.clear( );
		}
	// 检查
	currentVectorCount = result_run_node_item_info_vector.size( );
	if( currentVectorCount == 0 )
		return false;
	auto runNodeItemInfoArrayPtr = result_run_node_item_info_vector.data( );
	result_first_error_node_item_info_ptr = checkNodeItemBuilderVector( runNodeItemInfoArrayPtr, currentVectorCount );
	if( result_first_error_node_item_info_ptr != nullptr )
		return false;
	// 排序
	currentVectorCount = sortNodeItemVector( runNodeItemInfoArrayPtr, currentVectorCount );
	if( currentVectorCount == 0 )
		return false;
	result_run_node_item_info_vector.resize( currentVectorCount );
	return true;
}
bool NodeItemInfoVector::fillOutputNodeItemAtVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_out_node_item_info_ptr ) {
	size_t count = node_item_info->outputNodeItemVector.size( );
	if( count == 0 )
		return false;
	auto copySourceArrayPtr = node_item_info->outputNodeItemVector.data( );
	size_t oldCount = result_out_node_item_info_ptr.size( );
	size_t newCount = count + oldCount;
	result_out_node_item_info_ptr.resize( newCount );
	auto dataTargetPtr = result_out_node_item_info_ptr.data( );
	for( newCount = 0; newCount < count; ++newCount )
		dataTargetPtr[ oldCount + newCount ] = copySourceArrayPtr[ newCount ];
	for( newCount = 0; newCount < count; ++newCount )
		if( copySourceArrayPtr[ newCount ] )
			fillOutputNodeItemAtVector( copySourceArrayPtr[ newCount ], result_out_node_item_info_ptr );
	return true;
}
bool NodeItemInfoVector::fillInputNodeItemAtVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_in_node_item_info_ptr ) {
	size_t count = node_item_info->outputNodeItemVector.size( );
	if( count == 0 )
		return false;
	auto copySourceArrayPtr = node_item_info->inputNodeItemInfoVector.data( );
	size_t oldCount = result_in_node_item_info_ptr.size( );
	size_t newCount = count + oldCount;
	result_in_node_item_info_ptr.resize( newCount );
	auto dataTargetPtr = result_in_node_item_info_ptr.data( );
	for( newCount = 0; newCount < count; ++newCount )
		dataTargetPtr[ oldCount + newCount ] = copySourceArrayPtr[ newCount ];
	for( newCount = 0; newCount < count; ++newCount )
		if( copySourceArrayPtr[ newCount ] )
			fillInputNodeItemAtVector( copySourceArrayPtr[ newCount ], result_in_node_item_info_ptr );
	return true;
}
const NodeItemInfo * NodeItemInfoVector::checkNodeItemBuilderVector( const NodeItemInfo *const*const runNodeItemInfoArrayPtr, const size_t &currentVectorCount ) {
	if( currentVectorCount == 0 || runNodeItemInfoArrayPtr == nullptr )
		return nullptr;
	size_t checkIndex;
	size_t checkInputIndex;
	size_t currentVectorIndex;
	for( currentVectorIndex = 0; currentVectorIndex < currentVectorCount; ++currentVectorIndex ) {
		if( runNodeItemInfoArrayPtr[ currentVectorIndex ] == nullptr )
			continue;
		auto &inputNodeItemVector = runNodeItemInfoArrayPtr[ currentVectorIndex ]->getInputNodeItemVector( );
		size_t inputCount = inputNodeItemVector.size( );
		if( inputCount == 0 )
			continue;
		auto inputArrayPtr = inputNodeItemVector.data( );
		for( checkInputIndex = 0; checkInputIndex < inputCount; ++checkInputIndex ) {
			for( checkIndex = 0; checkIndex < currentVectorCount; ++checkIndex )
				if( inputArrayPtr[ checkInputIndex ] == nullptr || inputArrayPtr[ checkInputIndex ]->nodeItem->getNodeMetaType( ) == nodeItemEnum::Node_Item_Type::Begin || runNodeItemInfoArrayPtr[ checkIndex ] == inputArrayPtr[ checkInputIndex ] )
					break;
			if( checkIndex == currentVectorCount )
				return inputArrayPtr[ checkInputIndex ];
		}
	}
	return nullptr;
}
size_t NodeItemInfoVector::sortNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_count ) {

	size_t newCount = 0;
	size_t currentVectorIndex = 0;
	for( ; currentVectorIndex < inster_node_item_info_count; ++currentVectorIndex )
		if( node_item_info_array_ptr[ currentVectorIndex ] != nullptr )
			newCount += 1;

	size_t buffIndex = 0;
	currentVectorIndex = 0;
	using node_item_info_ptr_t = NodeItemInfo *;
	node_item_info_ptr_t *buff = new node_item_info_ptr_t [ newCount ];
	for( ; currentVectorIndex < inster_node_item_info_count; ++currentVectorIndex )
		if( node_item_info_array_ptr[ currentVectorIndex ] != nullptr )
			buff[ buffIndex++ ] = node_item_info_array_ptr[ currentVectorIndex ];

	buffIndex = 0;
	currentVectorIndex = 0;
	size_t inputIndex;
	size_t inputArrayCount;
	NodeItemInfo **inputArrayPtr;
	size_t nullPtrIndex = 0;
	// 排序
	for( ; buffIndex < newCount; ++buffIndex ) {
		inputArrayCount = buff[ buffIndex ]->inputNodeItemInfoVector.size( );
		if( inputArrayCount == 0 ) {
			node_item_info_array_ptr[ currentVectorIndex ] = buff[ buffIndex ];
			buff[ buffIndex ] = buff[ nullPtrIndex ];
			buff[ nullPtrIndex ] = nullptr;
			++nullPtrIndex;
			++currentVectorIndex;
			continue;
		}
		inputArrayPtr = buff[ buffIndex ]->inputNodeItemInfoVector.data( );
		// 输入全部等于 nullptr 时，放入无输入队列 (Begin 类型即 nullptr)
		inputIndex = 0;
		for( ; inputIndex < inputArrayCount; ++inputIndex )
			if( inputArrayPtr[ inputIndex ] != nullptr && inputArrayPtr[ inputIndex ]->nodeItem->getNodeMetaType( ) != nodeItemEnum::Node_Item_Type::Begin )
				break;
		if( inputIndex < inputArrayCount )
			continue;
		node_item_info_array_ptr[ currentVectorIndex ] = buff[ buffIndex ];
		++currentVectorIndex;
		buff[ buffIndex ] = buff[ nullPtrIndex ];
		buff[ nullPtrIndex ] = nullptr;
		++nullPtrIndex;
	}
	// 存储的起始地址
	auto nodeItemInfoArratOffsetPtr = node_item_info_array_ptr + nullPtrIndex;
	auto buffArratOffsetPtr = buff + nullPtrIndex;
	// 末尾
	auto nodeItemInfoArratOffsetCount = newCount - nullPtrIndex;

	size_t useCount;
	do {
		useCount = NodeItemInfoVector::fillNodeItemInfoVector( buffArratOffsetPtr, nodeItemInfoArratOffsetCount, nodeItemInfoArratOffsetPtr, nodeItemInfoArratOffsetCount, [&nullPtrIndex, node_item_info_array_ptr] ( NodeItemInfo *check ) {
			for( auto inputNodeItem : check->inputNodeItemInfoVector ) {
				for( size_t compIndex = 0; compIndex < nullPtrIndex; ++compIndex )
					if( inputNodeItem == node_item_info_array_ptr[ compIndex ] )
						return true;
				return false;
			}
			return false;
		} );
		if( useCount == 0 ) {
			auto buffOut = NodeItemInfoVector::formatNodeInfoPath( buff, newCount, ", " );
			auto srcOut = NodeItemInfoVector::formatNodeInfoPath( node_item_info_array_ptr, newCount, ", " );
			QString msg( "buff > %1\nsrc > %2" );
			tools::debug::printError( msg.arg( buffOut ).arg( srcOut ) );
			newCount = 0;
			break;
		}
		nullPtrIndex += useCount;
		buffArratOffsetPtr = buff + nullPtrIndex;
		nodeItemInfoArratOffsetPtr = node_item_info_array_ptr + nullPtrIndex;
		nodeItemInfoArratOffsetCount = newCount - nullPtrIndex;
	} while( nullPtrIndex != newCount );

	delete[] buff;
	return newCount;
}
