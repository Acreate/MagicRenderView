#include "nodeDirector.h"
#include <QMenu>

#include <node/stack/nodeStack.h>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"

#include "../node/node/node.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"
#include "../node/stack/baseNodeStack/baseNodeStack.h"

#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"

#include "../win/mainWindow.h"

bool NodeDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	varDirector = instancePtr->getVarDirector( );
	releaseMenu( );
	if( nodeVarDirector )
		delete nodeVarDirector;
	nodeVarDirector = new VarDirector;
	if( nodeVarDirector->init( ) == false )
		return false;
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

		QMenu *generateCreateMenu = fromNodeGenerateCreateMenu( nodeStackArrayPtr[ index ] );
		if( generateCreateMenu == nullptr )
			continue;
		this->nodeCreateMenu->addMenu( generateCreateMenu );
	}
	connect( this, &NodeDirector::release_link_signal, this, &NodeDirector::releaseLink );
	connect( this, &NodeDirector::create_link_signal, this, &NodeDirector::createLink );
	return true;
}
void NodeDirector::releaseLink( InputPort *signal_port, OutputPort *target_prot ) {

}
void NodeDirector::createLink( InputPort *signal_port, OutputPort *target_prot ) {

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
NodeClickInfo * NodeDirector::getNodeAtPos( const QPoint &point ) {
	return nullptr;
}
QMenu * NodeDirector::fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr ) {
	return nullptr;
}

bool NodeDirector::createMenuAtNodeType( NodeStack *node_stack_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function ) {

	return true;
}
bool NodeDirector::connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function ) {
	if( connect_qaction_ptr == nullptr || connect_qaction_fun_ptr == nullptr )
		return false;
	connect( connect_qaction_ptr, connect_qaction_fun_ptr, [this,action_click_function, node_type_name]( ) {
		auto node = action_click_function( );
		MainWindow *mainWindow = instancePtr->getMainWindow( );
		if( mainWindow == nullptr ) {
			auto errorMsg = tr( "无法匹配主窗口[Application::]getMainWindow( )" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg );
			delete node;
			return;
		}
		MainWidget *mainWidget = mainWindow->getMainWidget( );
		if( mainWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配主渲染组件[MainWindow::getMainWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::MainWidget_Nullptr, errorMsg );
			delete node;
			return;
		}
		DrawNodeWidget *drawNodeWidget = mainWidget->getDrawNodeWidget( );
		if( drawNodeWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配节点渲染组件 [MainWidget::getDrawNodeWidget()]" );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::DrawNodeWidget_Nullptr, errorMsg );
			delete node;
			return;
		}
		if( drawNodeWidget->addNode( node ) == false ) {
			auto errorMsg = tr( "节点添加失败[DrawNodeWidget::addNode( Node *add_node )]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::DrawNodeWidget_Add, errorMsg );
			delete node;
			return;
		}
		if( node->parent( ) != drawNodeWidget ) {
			auto errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg );
			delete node;
			return;
		}
		node->show( );
	} );
	return true;
}
