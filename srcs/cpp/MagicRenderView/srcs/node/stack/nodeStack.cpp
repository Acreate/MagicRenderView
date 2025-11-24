#include "nodeStack.h"
NodeStack::NodeStack( QObject *parent ) : QObject( parent ) { }
NodeStack::~NodeStack( ) {
}
Node * NodeStack::createNode( const QString &node_type_name ) {
	size_t count = nodeGenerate.size( );
	if( count == 0 )
		return nullptr;
	auto nodeGenerateArrayPtr = nodeGenerate.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeGenerateArrayPtr[ index ].first == node_type_name )
			return nodeGenerateArrayPtr[ index ].second( );
	return nullptr;
}
