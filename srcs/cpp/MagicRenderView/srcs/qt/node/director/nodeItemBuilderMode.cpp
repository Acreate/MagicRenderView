#include "nodeItemBuilderMode.h"

#include "nodeItemInfo.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
std_vector_shared_unity_shared< NodeItemBuilderMode > NodeItemBuilderMode::generateNodeItemBuilderModeVector( const std_vector< NodeItemInfo * > &start_node_item_info_vector, const std_vector< NodeItemInfo * > &normal_node_item_info_vector ) {
	size_t startNodeCount = start_node_item_info_vector.size( );
	if( startNodeCount == 0 ) {
		tools::debug::printError( "不存在匹配的开始节点" );
		return nullptr; // 没有结束节点，则返回
	}

	// todo : 实现返回
	std_vector_shared_unity_shared< NodeItemBuilderMode > result( new std_vector_unity_shared< NodeItemBuilderMode > );



	
	
	
	return result;
}
std_vector_shared_unity_shared< NodeItemBuilderMode > NodeItemBuilderMode::generateNodeItemBuilderModeVector( const std_vector< NodeItemInfo * > &node_item_info_vector ) {

	// 节点数量
	size_t builderNodeCount = node_item_info_vector.size( );
	// 节点数组基址
	auto builderNodeArrayPtr = node_item_info_vector.data( );
	// 当前遍历下标
	size_t index = 0;
	// 查找 开始节点
	std_vector< NodeItemInfo * > startNodeItem;
	std_vector< NodeItemInfo * > normalNodeItem;
	nodeItemEnum::Node_Item_Type result;
	QString error( "%1 节点异常" );
	for( ; index < builderNodeCount; ++index )
		if( builderNodeArrayPtr[ index ]->getNodeItemType( result ) )
			switch( result ) {
				case nodeItemEnum::Node_Item_Type::None :
					tools::debug::printError( error.arg( builderNodeArrayPtr[ index ]->nodeItem->getMetaObjectPathName( ) ) );
					break;
				case nodeItemEnum::Node_Item_Type::Root :
					startNodeItem.emplace_back( builderNodeArrayPtr[ index ] );
					break;
				case nodeItemEnum::Node_Item_Type::End :
				case nodeItemEnum::Node_Item_Type::Process :
				case nodeItemEnum::Node_Item_Type::Logic :
				case nodeItemEnum::Node_Item_Type::Point :
				case nodeItemEnum::Node_Item_Type::Jump :
					normalNodeItem.emplace_back( builderNodeArrayPtr[ index ] );
					break;
			}
	return NodeItemBuilderMode::generateNodeItemBuilderModeVector( startNodeItem,normalNodeItem );
}
bool NodeItemBuilderMode::getRunNodeItems( std_vector< NodeItemInfo * > &result_current_run_info_vector ) {
	result_current_run_info_vector = runNodeItemInfoVector;
	return result_current_run_info_vector.size( ) != 0;
}
