#include "./INodeStack.h"

std_vector< std_shared_ptr< INodeStack > > INodeStack::instanceVector;
INodeStack::~INodeStack( ) {
	for( auto nodeWidget : storageNode )
		if( nodeWidget.first->parent( ) == nullptr )
			delete nodeWidget.first;
}
INodeWidget * INodeStack::setStorageNode( INodeWidget *storage_obj, const QString &storage_name ) {
	if( storage_obj == nullptr )
		return nullptr;
	auto iterator = storageNode.begin( );
	auto end = storageNode.end( );
	INodeWidget *result = nullptr;
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			result = iterator->first;
			storageNode.erase( iterator );
			storageNode.emplace_back( storage_obj, storage_name );
			break;
		}
	return result;
}
INodeWidget * INodeStack::getStorageNode( const QString &storage_name ) const {
	auto iterator = storageNode.begin( );
	auto end = storageNode.end( );
	INodeWidget *result = nullptr;
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name )
			return iterator->first;
	return result;
}
INodeWidget * INodeStack::removeStorageNode( const QString &storage_name ) {
	auto iterator = storageNode.begin( );
	auto end = storageNode.end( );
	INodeWidget *result = nullptr;
	for( ; iterator != end; ++iterator )
		if( iterator->second == storage_name ) {
			result = iterator->first;
			storageNode.erase( iterator );
			break;
		}
	return result;
}
