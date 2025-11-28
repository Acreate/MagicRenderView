#include "nodeStack.h"

#include <QMenu>

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../node/node.h"
bool NodeStack::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	releaseMainMenu( );
	return true;
}
bool NodeStack::appendNodeGenerateUnity( const QString &name, const std::function< Node *( ) > &generate_function ) {
	nodeGenerate.insert( nodeGenerate.begin( ), std::pair( name, generate_function ) );
	return true;
}
NodeStack::NodeStack( QObject *parent ) : QObject( parent ), mainMenu( nullptr ) { }
void NodeStack::releaseMainMenu( ) {
	size_t count;
	size_t index;

	count = actions.size( );
	if( count ) {
		auto actionArrayPtr = actions.data( );
		for( index = 0; index < count; ++index )
			delete actionArrayPtr[ index ].second;
		actions.clear( );
	}

	count = subMenus.size( );
	if( count ) {
		auto subMenuArrayPtr = subMenus.data( );
		for( index = 0; index < count; ++index )
			delete subMenuArrayPtr[ index ].second;
		subMenus.clear( );
	}
	if( mainMenu )
		delete mainMenu;
	mainMenu = nullptr;
}
NodeStack::~NodeStack( ) {
	releaseMainMenu( );
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
