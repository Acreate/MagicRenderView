#include "nodeItemBuilderObj.h"

#include "nodeItemInfo.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
NodeItemBuilderObj::NodeItemBuilderObj( QObject *parent ) : QObject( parent ), moduleBuilderStaus( nodeItemEnum::Node_Item_Builder_Type::None ) {
	currentVectorIndex = 0;
	currentVectorCount = 0;
	runNodeItemInfoArrayPtr = nullptr;
}
bool NodeItemBuilderObj::addBuilderNodeItem( NodeItemInfo *node_item_info ) {
	auto nodeMetaType = node_item_info->nodeItem->getNodeMetaType( );
	if( nodeMetaType != nodeItemEnum::Node_Item_Type::Begin )
		return false;
	currentVectorCount = startNodeItemInfoVector.size( );
	runNodeItemInfoArrayPtr = startNodeItemInfoVector.data( );
	currentVectorIndex = 0;
	for( ; currentVectorIndex < currentVectorCount; ++currentVectorIndex )
		if( runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem == node_item_info->nodeItem )
			return false;
	startNodeItemInfoVector.emplace_back( node_item_info );
	return true;
}
bool NodeItemBuilderObj::builderNodeItemVector( ) {
	currentVectorIndex = 0;
	currentVectorCount = 0;
	runNodeItemInfoArrayPtr = nullptr;
	runNodeItemInfoVector.clear( );
	currentVectorCount = startNodeItemInfoVector.size( );
	if( currentVectorCount == 0 )
		return false;
	runNodeItemInfoArrayPtr = startNodeItemInfoVector.data( );
	std_vector< NodeItemInfo * > resultOutNodeItemInfoPtr;
	for( ; currentVectorIndex < currentVectorCount; ++currentVectorIndex )
		if( fillNodeItemVector( runNodeItemInfoArrayPtr[ currentVectorIndex ], resultOutNodeItemInfoPtr ) == true ) {
			runNodeItemInfoVector.append_range( resultOutNodeItemInfoPtr );
			resultOutNodeItemInfoPtr.clear( );
		}
	currentVectorCount = runNodeItemInfoVector.size( );
	currentVectorIndex = 0;
	if( currentVectorCount == 0 ) {
		runNodeItemInfoArrayPtr = nullptr;
		runNodeItemInfoVector.clear( );
		return false;
	}
	// 检查
	runNodeItemInfoArrayPtr = runNodeItemInfoVector.data( );
	currentVectorCount = runNodeItemInfoVector.size( );
	size_t checkIndex;
	size_t checkInputIndex;
	for( ; currentVectorIndex < currentVectorCount; ++currentVectorIndex ) {
		auto &inputNodeItemVector = runNodeItemInfoArrayPtr[ currentVectorIndex ]->getInputNodeItemVector( );
		size_t inputCount = inputNodeItemVector.size( );
		if( inputCount == 0 )
			continue;
		auto inputArrayPtr = inputNodeItemVector.data( );
		for( checkInputIndex = 0; checkInputIndex < inputCount; ++checkInputIndex ) {
			for( checkIndex = 0; checkIndex < currentVectorCount; ++checkIndex )
				if( runNodeItemInfoArrayPtr[ checkIndex ] == inputArrayPtr[ checkInputIndex ] )
					break;
			if( checkIndex != currentVectorCount ) {
				auto metaObjectPathName = inputArrayPtr[ checkInputIndex ]->nodeItem->getMetaObjectPathName( );
				QString msg( "%1->%2 未存在输入依赖链当中" );
				tools::debug::printError( msg.arg( metaObjectPathName ).arg( inputArrayPtr[ checkInputIndex ]->nodeItem->generateCode ) );
				currentVectorIndex = 0;
				currentVectorCount = 0;
				runNodeItemInfoArrayPtr = nullptr;
				runNodeItemInfoVector.clear( );
				return false;
			}
		}
	}
	// 排序
	sortNodeItemVector( runNodeItemInfoArrayPtr, currentVectorCount );
	return true;
}
bool NodeItemBuilderObj::fillNodeItemVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_out_node_item_info_ptr ) {

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
		fillNodeItemVector( copySourceArrayPtr[ newCount ], result_out_node_item_info_ptr );
	return true;
}
void NodeItemBuilderObj::sortNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_count ) {
}

void NodeItemBuilderObj::moveNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_source_point, const size_t &inster_node_item_info_target_point ) {
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
NodeItemBuilderObj::~NodeItemBuilderObj( ) { }
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::builderStatus( ) const {
	return moduleBuilderStaus;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::runCurrentNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Error;

	return nodeItemEnum::Node_Item_Builder_Type::Finish;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::nextNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	return nodeItemEnum::Node_Item_Builder_Type::Finish;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::toStartNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	return nodeItemEnum::Node_Item_Builder_Type::Start;
}
bool NodeItemBuilderObj::getInfo( QString &result_msg ) const {
	if( moduleBuilderStaus == nodeItemEnum::Node_Item_Builder_Type::None )
		return false;
	result_msg = msg;
	return true;
}
