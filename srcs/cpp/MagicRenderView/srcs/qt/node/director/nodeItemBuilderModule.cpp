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

	std_vector< NodeItemBuilderModule * > result;

	size_t index = 0;
	NodeItemBuilderModule *element;

	for( ; index < node_item_info_array_count; ++index )
		if( node_item_info_array_ptr[ index ]->nodeItem->getNodeMetaType( ) == nodeItemEnum::Node_Item_Type::End ) {
			auto endAtStartNode = findEndAtStartNode( node_item_info_array_ptr[ index ] );
			if( endAtStartNode.size( ) == 0 )
				continue;
			size_t resultCount = result.size( );
			auto resultArrayPtr = result.data( );
			size_t resultIndex = 0;
			size_t endAtStartNodeCount = endAtStartNode.size( );
			auto endAtStartNodeArrayPtr = endAtStartNode.data( );
			size_t endAtStartNodeIndex = 0;
			element = nullptr;
			for( ; resultIndex < resultCount; ++resultIndex ) {
				element = resultArrayPtr[ resultIndex ];
				size_t existStartCount = element->startNodeItemInfoVector.size( );
				auto existArrayPtr = element->startNodeItemInfoVector.data( );
				size_t existIndex = 0;
				for( ; existIndex < existStartCount; ++existIndex ) {
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
					element = nullptr;
					break;
				}
			}
			if( element == nullptr )
				continue;
			element = new NodeItemBuilderModule;
			element->startNodeItemInfoVector = endAtStartNode;
			result.emplace_back( element );
		}

	return result;

}
