#include "nodeDirector.h"
#include <QMenu>

#include <node/stack/nodeStack.h>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"

#include "../node/node/node.h"
#include "../node/stack/baseNodeStack/baseNodeStack.h"

bool NodeDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	varDirector = instancePtr->getVarDirector( );
	releaseMenu( );
	if( nodeVarDirector )
		delete nodeVarDirector;
	nodeVarDirector = new VarDirector;
	size_t count;
	size_t index;
	NodeStack **nodeStackArrayPtr;

	// 这里加入节点窗口创建函数
	nodeStacks.emplace_back( new BaseNodeStack( nodeVarDirector ) );

	// 初始化列表
	count = nodeStacks.size( );
	nodeStackArrayPtr = nodeStacks.data( );
	for( index = 0; index < count; ++index )
		if( nodeStackArrayPtr[ index ]->init( ) == false ) {
			auto className = nodeStackArrayPtr[ index ]->metaObject( )->className( );
			QString msg( "[ %1 ]节点堆栈类初始化失败" );
			printerDirector->error( msg.arg( className ) );
			for( index = 0; index < count; ++index )
				delete nodeStackArrayPtr[ index ];
			nodeStacks.clear( );
			return false;
		}
	// 初始化菜单
	nodeCreateMenu = new QMenu;
	for( index = 0; index < count; ++index ) {
		connect( nodeStackArrayPtr[ index ], &NodeStack::finish_create_signal, this, &NodeDirector::finish_create_signal );
		connect( nodeStackArrayPtr[ index ], &NodeStack::error_create_signal, this, &NodeDirector::error_create_signal );
		nodeCreateMenu->addMenu( nodeStackArrayPtr[ index ]->getMainMenu( ) );
	}

	return true;
}
NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ), nodeCreateMenu( nullptr ), nodeVarDirector( nullptr ) {

}
void NodeDirector::releaseMenu( ) {
	auto count = nodeStacks.size( );
	if( count ) {
		auto nodeStackArrayPtr = nodeStacks.data( );
		for( decltype(count) index = 0; index < count; ++index )
			delete nodeStackArrayPtr[ index ];
		nodeStacks.clear( );
	}
	if( nodeCreateMenu )
		delete nodeCreateMenu;
	nodeCreateMenu = nullptr;
}
NodeDirector::~NodeDirector( ) {
	releaseMenu( );
	if( nodeVarDirector )
		delete nodeVarDirector;
}
Node * NodeDirector::createNode( const QString &stack_name, const QString &node_type_name ) {
	auto count = nodeStacks.size( );
	if( count == 0 )
		return nullptr;
	auto nodeStackArrayPtr = nodeStacks.data( );
	for( decltype(count) index = 0; index < count; ++index )
		if( nodeStackArrayPtr[ index ]->objectName( ) == stack_name ) {
			Node *node = nodeStackArrayPtr[ index ]->createNode( node_type_name );
			if( node == nullptr )
				return nullptr;
			connect( node, &Node::error_node_signal, this, &NodeDirector::error_node_signal );
			connect( node, &Node::advise_node_signal, this, &NodeDirector::advise_node_signal );
			connect( node, &Node::finish_node_signal, this, &NodeDirector::finish_node_signal );
		}
	return nullptr;
}
