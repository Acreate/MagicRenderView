#include "nodeItemInfo.h"

#include <qt/node/item/nodeItem.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>
NodeItemInfo::~NodeItemInfo( ) {
	emit releaseThisPtr( this );
	delete manageMenu;
}
NodeItemInfo::NodeItemInfo( NodeItem *node_item ) : QObject( nullptr ),
	nodeItem( node_item ) {
	manageMenu = new QMenu;
	QString title( "删除[ %1 ]节点" );
	auto addAction = manageMenu->addAction( title.arg( node_item->getMetaObjectPathName( ) ) );
	connect( addAction, &QAction::triggered, [this]( ) {
		nodeItem->deleteLater( );
	} );
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
void NodeItemInfoVector::moveNodeItemVector( NodeItemInfoArrayPtr node_item_info_array_ptr, const size_t &inster_node_item_info_source_point, const size_t &inster_node_item_info_target_point ) {
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
QString NodeItemInfoVector::formatNodeInfoPath( NodeItemInfoArrayPtr node_item_info, const size_t &count, const QString &join_string ) {
	QStringList out;
	QString formatString( "%1(%2)" );
	for( size_t index = 0; index < count; ++index )
		out.append( formatString.arg( node_item_info[ index ]->getNodeItem( )->getMetaObjectPathName( ) ).arg( node_item_info[ index ]->getNodeItem( )->getGenerateCode( ) ) );
	return out.join( join_string );
}
size_t NodeItemInfoVector::fillNodeItemInfoVector( NodeItemInfoArrayPtr source_node_item_info_array_ptr, const size_t &source_node_item_info_array_count, NodeItemInfoArrayPtr target_node_item_info_array_ptr, const size_t &target_node_item_info_array_count, const std_function< bool( NodeItemInfo *check ) > &fill_check_function ) {
	size_t fillCount = 0;
	for( size_t sourceIndex = 0; sourceIndex < source_node_item_info_array_count; ++sourceIndex )
		if( fillCount == target_node_item_info_array_count )
			return fillCount;
		else if( fill_check_function( source_node_item_info_array_ptr[ sourceIndex ] ) )
			target_node_item_info_array_ptr[ fillCount++ ] = source_node_item_info_array_ptr[ sourceIndex ];
	return fillCount;
}
