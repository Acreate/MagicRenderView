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
	for( ; index < node_item_info_array_count; ++index )
		if( node_item_info_array_ptr[ index ]->nodeItem->getNodeMetaType( ) == nodeItemEnum::Node_Item_Type::End ) {
			auto endAtStartNode = findEndAtStartNode( node_item_info_array_ptr[ index ] );

		}

	return result;

}
