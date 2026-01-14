#include "nodeStack.h"

#include <QMenu>

#include "../../app/application.h"

#include "../../director/printerDirector.h"
#include "../../tools/path.h"

#include "../node/node.h"
bool NodeStack::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	nodeGenerate.clear( );
	return true;
}
bool NodeStack::appendNodeGenerateUnity( const QString &name, const std::function< Node *( const QString & ) > &generate_function ) {
	auto normalPathSeparatorToPath = path::normalPathSeparatorToPath( name );
	nodeGenerate.emplace_back( std::pair( normalPathSeparatorToPath, generate_function ) );
	return true;
}
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
			return nodeGenerateArrayPtr[ index ].second( node_type_name );
	return nullptr;
}
