#include "./nodeLinkVector.h"

#include "../nodeWidget/INodeWidget.h"
NodeLinkVector::NodeLinkVector( ) {
	mutex.reset( new std_mutex );
	nodeLinkItems.reset( new std_vector< NodeLinkItem > );
}
bool NodeLinkVector::usRegNodeLinkStatus( INodeWidget *node_widget ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	if ( tools::vector::has( nodeWidgetLinkStatus, node_widget ) == true )
		return true;
	nodeWidgetLinkStatus.emplace_back( node_widget );
	std_vector< INodeComponent * > nodeComponents = node_widget->getNodeComponents( );
	if ( nodeComponents.size( ) == 0 )
		return false;
	for ( auto &item : nodeComponents )
		if ( tools::vector::has( nodeComponentLinkStatus, { item, node_widget } ) == false )
			nodeComponentLinkStatus.emplace_back( item, node_widget );
	return true;
}
bool NodeLinkVector::unRegNodeLinkStatus( INodeWidget *node_widget ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	bool result = true;
	if ( nodeComponentLinkStatus.size( ) == 0 || nodeLinkItems->size( ) == 0 )
		return result;

	auto nodeWidgetBegin = nodeWidgetLinkStatus.begin( );
	auto nodeWidgetEnd = nodeWidgetLinkStatus.end( );
	for ( ; nodeWidgetBegin != nodeWidgetEnd; ++nodeWidgetBegin )
		if ( *nodeWidgetBegin == node_widget ) {
			nodeWidgetLinkStatus.erase( nodeWidgetBegin );
			break;
		}
	if ( nodeWidgetBegin == nodeWidgetEnd )
		return false;
	std_vector< INodeComponent * > nodeComponents = node_widget->getNodeComponents( );
	if ( nodeComponents.size( ) == 0 )
		return result;
	for ( auto &item : nodeComponents ) {
		auto iterator = nodeComponentLinkStatus.begin( );
		auto end = nodeComponentLinkStatus.end( );
		for ( ; iterator != end; ++iterator )
			if ( iterator->first == item && iterator->second == node_widget ) {
				nodeComponentLinkStatus.erase( iterator );
				while ( true ) {
					auto rmeoveIter = nodeLinkItems->begin( );
					auto nodeComponentEnd = nodeLinkItems->end( );
					for ( ; rmeoveIter != nodeComponentEnd; ++rmeoveIter ) {
						auto nodeComponentInfo = rmeoveIter->getInputNodeComponentInfo( );
						if ( nodeComponentInfo.first == node_widget && nodeComponentInfo.second == item ) {
							nodeLinkItems->erase( rmeoveIter );
							break;
						}
						nodeComponentInfo = rmeoveIter->getOutputNodeComponentInfo( );
						if ( nodeComponentInfo.first == node_widget && nodeComponentInfo.second == item ) {
							nodeLinkItems->erase( rmeoveIter );
							break;
						}
					}
					if ( rmeoveIter == nodeComponentEnd )
						break; // 删除完毕
				}
				break;
			}
		if ( iterator == end ) {
			result = false;
			break;
		}
	}
	return result;
}
std_vector< NodeLinkItem > NodeLinkVector::toVector( ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	return *nodeLinkItems;
}
void NodeLinkVector::resetVector( const std_vector< NodeLinkItem > &conver ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = conver.size( );
	auto sourcePtr = conver.data( );
	nodeLinkItems->resize( count );
	auto targetDataPtr = nodeLinkItems->data( );;
	for ( size_t index = 0; index < count; ++index )
		targetDataPtr[ index ] = sourcePtr[ index ];
}
bool NodeLinkVector::hasItem( const NodeLinkItem &item ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return false;
	auto nodeLinkItemPtr = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index )
		if ( nodeLinkItemPtr[ index ] == item )
			return true;
	return false;
}

bool NodeLinkVector::emplace_back( const NodeLinkItem &item ) {
	std_lock_grad_mutex lockGradMutex( *mutex );

	size_t count = nodeWidgetLinkStatus.size( );
	if ( count == 0 )
		return false;
	size_t regComponetCount = 0;
	size_t index = 0;
	auto inputNodeComponentInfo = item.getInputNodeComponentInfo( );
	auto outputNodeComponentInfo = item.getOutputNodeComponentInfo( );

	auto pair = nodeWidgetLinkStatus.data( );

	for ( index = 0; index < count && regComponetCount != 2; ++index ) {
		auto iter = pair[ index ];
		if ( iter == inputNodeComponentInfo.first ) {
			++regComponetCount;
			inputNodeComponentInfo.first = nullptr;
			inputNodeComponentInfo.second = nullptr;
			continue;
		} else if ( iter == outputNodeComponentInfo.first ) {
			++regComponetCount;
			outputNodeComponentInfo.first = nullptr;
			outputNodeComponentInfo.second = nullptr;
			continue;
		}
	}

	if ( regComponetCount != 2 ) // 没有注册组件
		return false;

	count = nodeLinkItems->size( );
	if ( count == 0 ) {
		nodeLinkItems->emplace_back( item );
		return true;
	}
	auto nodeLinkItemPtr = nodeLinkItems->data( );
	for ( index = 0; index < count; ++index )
		if ( nodeLinkItemPtr[ index ] == item )
			return false;
	nodeLinkItems->emplace_back( item );
	return true;
}

int NodeLinkVector::hasUnity( const INodeComponent *unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	int has;
	for ( size_t index = 0; index < count; ++index )
		if ( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}

int NodeLinkVector::hasUnity( const INodeWidget *unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	int has;
	for ( size_t index = 0; index < count; ++index )
		if ( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}
int NodeLinkVector::hasInputUnity( const INodeComponent *input_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index )
		if ( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeLinkVector::hasInputUnity( const INodeWidget *input_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index )
		if ( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeLinkVector::hasOutputUnity( const INodeComponent *output_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index )
		if ( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeLinkVector::hasOutputUnity( const INodeWidget *output_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index )
		if ( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeLinkVector::removeNodeComponentItem( const INodeComponent *unity ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	size_t result = 0;
	while ( true ) {
		auto iterator = nodeLinkItems->begin( );
		auto end = nodeLinkItems->end( );
		for ( ; iterator != end; ++iterator )
			if ( iterator->has( unity ) ) {
				nodeLinkItems->erase( iterator );
				break;
			}
		if ( iterator == end )
			break;
	}

	return result;
}
int NodeLinkVector::removeFirstInputItem( const INodeComponent *input_unity ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	auto iterator = nodeLinkItems->begin( );
	auto end = nodeLinkItems->end( );
	for ( ; iterator != end; ++iterator )
		if ( iterator->hasInput( input_unity ) ) {
			nodeLinkItems->erase( iterator );
			return 1;
		}
	return 0;
}
int NodeLinkVector::removeFirstOutputItem( const INodeComponent *output_unity ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	auto iterator = nodeLinkItems->begin( );
	auto end = nodeLinkItems->end( );
	for ( ; iterator != end; ++iterator )
		if ( iterator->hasOutput( output_unity ) ) {
			nodeLinkItems->erase( iterator );
			return 1;
		}
	return 0;
}
int NodeLinkVector::removeFirstItem( const INodeComponent *output_unity, const INodeComponent *input_unity ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	auto iterator = nodeLinkItems->begin( );
	auto end = nodeLinkItems->end( );
	for ( ; iterator != end; ++iterator )
		if ( iterator->hasInput( input_unity ) && iterator->hasOutput( output_unity ) ) {
			nodeLinkItems->erase( iterator );
			return 1;
		}
	return 0;
}
std_vector< NodeLinkItem > NodeLinkVector::getOutLinkItems( const INodeComponent *input_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	std_vector< NodeLinkItem > result;

	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return result;
	auto nodeLinkItem = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index ) {
		auto inputNodeComponentInfo = nodeLinkItem[ index ].getInputNodeComponentInfo( );
		if ( inputNodeComponentInfo.second == input_unity )
			result.emplace_back( nodeLinkItem[ index ] );
	}
	return result;
}
std_vector< NodeLinkItem > NodeLinkVector::getInLinkItems( const INodeComponent *ouutput_unity ) const {
	std_lock_grad_mutex lockGradMutex( *mutex );
	std_vector< NodeLinkItem > result;
	size_t count = nodeLinkItems->size( );
	if ( count == 0 )
		return result;
	auto nodeLinkItem = nodeLinkItems->data( );
	for ( size_t index = 0; index < count; ++index ) {
		auto inputNodeComponentInfo = nodeLinkItem[ index ].getOutputNodeComponentInfo( );
		if ( inputNodeComponentInfo.second == ouutput_unity )
			result.emplace_back( nodeLinkItem[ index ] );
	}
	return result;
}
std_mutex * NodeLinkVector::getMutex( ) const {
	return mutex.get( );
}
bool NodeLinkVector::lockMutex( ) const {
	if ( mutex->try_lock( ) )
		return true;
	return true;
}
bool NodeLinkVector::unMutex( ) const {
	if ( mutex->try_lock( ) ) {
		mutex.get( )->unlock( );
		return true;
	}
	mutex.get( )->unlock( );
	return true;
}
size_t NodeLinkVector::count( ) const {
	return nodeLinkItems->size( );
}
NodeLinkItem * NodeLinkVector::data( ) const {
	return nodeLinkItems->data( );
}
void NodeLinkVector::end( ) const {
	mutex->unlock( );
}
std_pairt< std_vector< NodeLinkItem >::iterator, std_vector< NodeLinkItem >::iterator > NodeLinkVector::begin( ) const {
	mutex->lock( );
	return { nodeLinkItems->begin( ), nodeLinkItems->end( ) };
}
void NodeLinkVector::clear( ) {
	std_lock_grad_mutex lockGradMutex( *mutex );
	nodeLinkItems->clear( );
}
void NodeLinkVector::reset( ) {

	std_lock_grad_mutex lockGradMutex( *mutex );
	nodeLinkItems->clear( );
	nodeWidgetLinkStatus.clear( );
	nodeComponentLinkStatus.clear( );
}
