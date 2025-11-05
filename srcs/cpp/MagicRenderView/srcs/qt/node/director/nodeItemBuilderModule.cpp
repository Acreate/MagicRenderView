#include "nodeItemBuilderModule.h"

#include "nodeItemInfo.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
std_vector< NodeItemInfo * > NodeItemBuilderModule::findEndAtStartNode( NodeItemInfo *end_node_info_ptr ) {

	std_vector< NodeItemInfo * > result;

	if( NodeItemInfoVector::fillInputNodeItemAtVector( end_node_info_ptr, result ) == false )
		return result;

	size_t count = result.size( );
	auto data = result.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ]->nodeItem->getNodeMetaType( ) != nodeItemEnum::Node_Item_Type::Begin )
			data[ index ] = nullptr;
	tools::vector::removeNullPtr( result );
	return result;
}
std_vector< NodeItemBuilderModule * > NodeItemBuilderModule::generateModuleVector( NodeItemInfo **node_item_info_array_ptr, const size_t &node_item_info_array_count ) {

	std_vector< NodeItemBuilderModule * > result; // 返回的模型列表
	NodeItemBuilderModule *element; // 临时操作模块对象指针
	NodeItemBuilderModule **resultArrayPtr; // 遍历用的返回模型列表序列指针
	std_vector< NodeItemInfo * > endAtStartNode; // 保存返回用的开始节点序列
	NodeItemInfo **endAtStartNodeArrayPtr;// 遍历保存返回用的开始节点序列
	NodeItemInfo **existArrayPtr;// 遍历已经生成的模块保存返回用的开始节点序列
	size_t index; // 输入数组下标
	size_t resultIndex; // 返回模块序列下标
	size_t resultCount; // 返回模块数量
	size_t endAtStartNodeIndex; // 返回的开始节点下标
	size_t endAtStartNodeCount; // 返回的开始节点个数
	size_t existIndex; // 遍历模块的开始节点下标
	size_t existStartCount; // 遍历模块的开始节点个数
	for( index = 0; index < node_item_info_array_count; ++index )
		if( node_item_info_array_ptr[ index ]->nodeItem->getNodeMetaType( ) == nodeItemEnum::Node_Item_Type::End ) {
			endAtStartNode = findEndAtStartNode( node_item_info_array_ptr[ index ] );
			if( endAtStartNode.size( ) == 0 )
				continue;
			resultCount = result.size( );
			resultArrayPtr = result.data( );
			endAtStartNodeCount = endAtStartNode.size( );
			endAtStartNodeArrayPtr = endAtStartNode.data( );
			element = nullptr;
			for( resultIndex = 0, endAtStartNodeIndex = 0; resultIndex < resultCount; ++resultIndex ) {
				element = resultArrayPtr[ resultIndex ];
				existStartCount = element->startNodeItemInfoVector.size( );
				existArrayPtr = element->startNodeItemInfoVector.data( );

				for( existIndex = 0; existIndex < existStartCount; ++existIndex ) {
					for( endAtStartNodeIndex = 0; endAtStartNodeIndex < endAtStartNodeCount; ++endAtStartNodeIndex )
						if( existArrayPtr[ existIndex ] == endAtStartNodeArrayPtr[ endAtStartNodeIndex ] )
							break;
					if( endAtStartNodeIndex != endAtStartNodeCount )
						break;
				}

				if( endAtStartNodeIndex != endAtStartNodeCount ) {
					for( existIndex = 0; existIndex < existStartCount; ++existIndex ) {
						for( endAtStartNodeIndex = 0; endAtStartNodeIndex < endAtStartNodeCount; ++endAtStartNodeIndex )
							if( existArrayPtr[ existIndex ] != endAtStartNodeArrayPtr[ endAtStartNodeIndex ] )
								break;
						if( endAtStartNodeIndex != endAtStartNodeCount )
							continue;
						element->startNodeItemInfoVector.emplace_back( endAtStartNodeArrayPtr[ endAtStartNodeIndex ] );
					}

					break;
				}
				element = nullptr;
			}
			if( element != nullptr )
				continue;
			element = new NodeItemBuilderModule;
			element->startNodeItemInfoVector = endAtStartNode;
			result.emplace_back( element );
		}

	return result;

}
