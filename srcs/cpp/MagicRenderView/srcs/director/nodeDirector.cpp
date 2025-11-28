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

		if( fromNodeGenerateCreateMenu( nodeStackArrayPtr[ index ] ) == false ) {
			continue;
		}
		nodeCreateMenu->addMenu( nodeStackArrayPtr[ index ]->getMainMenu( ) );
	}
	connect( this, &NodeDirector::release_link_signal, this, &NodeDirector::releaseLink );
	connect( this, &NodeDirector::create_link_signal, this, &NodeDirector::createLink );
	return true;
}
void NodeDirector::releaseLink( InputPort *signal_port, OutputPort *target_prot ) {
	// 获取输出输入端口节点
	Node *targetNode = target_prot->node;
	Node *signalNode = signal_port->node;
	//emit signalNode->release_link_signal( signal_port, target_prot );
	// 扫描当前节点所有输入端，检查其中是否存在依赖输出端口，存在则退出
	size_t count = signalNode->inputPortVector.size( );
	auto inputPortArrayPtr = signalNode->inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( inputPortArrayPtr[ index ]->refOutputPortHasNode( targetNode ) )
			return; // 仍然有输入端口依赖其节点

	// 释放输入节点当中匹配的依赖指针
	count = signalNode->inputNodeVector.size( );
	auto refNodeArrayPtr = signalNode->inputNodeVector.data( );
	index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == targetNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( refNodeArrayPtr[ index ] == nullptr )
		return;
	count -= 1;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == nullptr )
			break;
		else
			refNodeArrayPtr[ index ] = refNodeArrayPtr[ index + 1 ];
	// 释放输出节点中匹配的输入节点指针	
	count = targetNode->inputNodeVector.size( );
	refNodeArrayPtr = targetNode->inputNodeVector.data( );
	index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == signalNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( refNodeArrayPtr[ index ] == nullptr )
		return;
	count -= 1;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == nullptr )
			break;
		else
			refNodeArrayPtr[ index ] = refNodeArrayPtr[ index + 1 ];
	disconnect( targetNode, &Node::release_node_signal, signalNode, &Node::removeInputNode );
	emit signalNode->release_ref_node_signal( signalNode, targetNode );
}
void NodeDirector::createLink( InputPort *signal_port, OutputPort *target_prot ) {
	// 获取输出输入端口节点
	Node *targetNode = target_prot->node;
	Node *signalNode = signal_port->node;
	//emit signalNode->create_link_signal( signal_port, target_prot );
	// 输入依赖节点
	size_t count = signalNode->inputNodeVector.size( );
	auto refNodeArrayPtr = signalNode->inputNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == targetNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( index == count )
		signalNode->inputNodeVector.emplace_back( targetNode );
	else if( refNodeArrayPtr[ index ] == nullptr )
		refNodeArrayPtr[ index ] = targetNode;
	// 输出依赖节点
	count = targetNode->outputNodeVector.size( );
	refNodeArrayPtr = targetNode->outputNodeVector.data( );
	index = 0;
	for( ; index < count; ++index )
		if( refNodeArrayPtr[ index ] == signalNode || refNodeArrayPtr[ index ] == nullptr )
			break;
	if( index == count )
		signalNode->inputNodeVector.emplace_back( signalNode );
	else if( refNodeArrayPtr[ index ] == nullptr )
		refNodeArrayPtr[ index ] = signalNode;
	connect( targetNode, &Node::release_node_signal, signalNode, &Node::removeInputNode );
	emit signalNode->create_ref_node_signal( signalNode, targetNode );
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
bool NodeDirector::fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr ) {

	node_stack_ptr->mainMenu = new QMenu( node_stack_ptr->objectName( ) );
	size_t index;
	size_t count = node_stack_ptr->nodeGenerate.size( );
	auto nodeArrayPtr = node_stack_ptr->nodeGenerate.data( );
	for( index = 0; index < count; ++index )
		if( createMenuAtNodeType( node_stack_ptr, nodeArrayPtr[ index ].first, nodeArrayPtr[ index ].second ) == false ) {
			QString msg( "[ %1 ]节点菜单对象初始化失败" );
			printerDirector->error( msg.arg( nodeArrayPtr[ index ].first ) );
			node_stack_ptr->releaseMainMenu( );
			node_stack_ptr->nodeGenerate.clear( );
			return false;
		}
	count = node_stack_ptr->subMenus.size( );
	index = 0;
	auto subMenuArrayPtr = node_stack_ptr->subMenus.data( );
	for( ; index < count; ++index )
		if( subMenuArrayPtr[ index ].first.size( ) == 1 )
			node_stack_ptr->mainMenu->addMenu( subMenuArrayPtr[ index ].second );

	auto actionArrayPtr = node_stack_ptr->actions.data( );
	count = node_stack_ptr->actions.size( );
	index = 0;
	for( ; index < count; ++index )
		if( actionArrayPtr[ index ].first.size( ) == 1 )
			node_stack_ptr->mainMenu->addAction( actionArrayPtr[ index ].second );
	return true;
}

bool NodeDirector::createMenuAtNodeType( NodeStack *node_stack_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function ) {

	qsizetype qcharCount = node_type_name.length( );
	if( qcharCount == 0 )
		return false;
	QString buff;
	buff.resize( qcharCount );

	std::vector< QString > targetName;
	auto qcharArrayPtr = node_type_name.data( );
	auto buffArrayPtr = buff.data( );
	QString appendUnity;
	decltype(qcharCount) buffIndex = 0;
	decltype(qcharCount) index = 0;
	for( ; index < qcharCount; ++index )
		if( qcharArrayPtr[ index ] == '\\' || qcharArrayPtr[ index ] == '/' ) {
			if( buffIndex != 0 ) {
				appendUnity = QString( buffArrayPtr, buffIndex );
				targetName.emplace_back( appendUnity );
				buffIndex = 0;
			}
		} else {
			buffArrayPtr[ buffIndex ] = qcharArrayPtr[ index ];
			++buffIndex;
		}
	if( buffIndex != 0 ) {
		appendUnity = QString( buffArrayPtr, buffIndex );
		targetName.emplace_back( appendUnity );
	}

	size_t nameVectorCount = targetName.size( );
	if( nameVectorCount == 0 )
		return false;
	size_t foreachCount;
	size_t foreachIndex;
	QMenu *manu;
	std::pair< std::vector< QString >, QMenu * > *subMenuArrayPtr;
	std::vector< QString > compVector;
	size_t compVectorIndex;
	auto nameVectorArratPtr = targetName.data( );
	nameVectorCount -= 1; // 末尾名称作为 QAction 对象
	size_t nameVectorIndex = 0;
	size_t leftCount;
	size_t compVectorArrayCount;
	QString *compArrayPtr;
	QString *leftArray;
	if( nameVectorCount != 0 )
		do {
			compVector.emplace_back( nameVectorArratPtr[ nameVectorIndex ] );
			compVectorArrayCount = compVector.size( );
			compArrayPtr = compVector.data( );
			foreachCount = node_stack_ptr->subMenus.size( );
			foreachIndex = 0;
			subMenuArrayPtr = node_stack_ptr->subMenus.data( );
			for( ; foreachIndex < foreachCount; ++foreachIndex ) {
				leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
				if( leftCount != compVectorArrayCount )
					continue;
				leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
				for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
					if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
						break;
				if( compVectorIndex == compVectorArrayCount )
					break;
			}
			if( foreachIndex == foreachCount ) {
				manu = new QMenu( nameVectorArratPtr[ nameVectorIndex ] );
				// 寻找挂靠
				compVectorArrayCount -= 1;// 挂靠时。不需要末尾
				if( compVectorArrayCount != 0 ) {
					for( foreachIndex = 0; foreachIndex < foreachCount; ++foreachIndex ) {
						leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
						if( leftCount != compVectorArrayCount )
							continue;
						leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
						for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
							if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
								break;
						if( compVectorIndex == compVectorArrayCount )
							break;
					}
					if( foreachIndex == foreachCount ) {
						QString msg( "[ %1 ]节点菜单对象不存在挂靠的 QMenu" );
						printerDirector->error( msg.arg( appendUnity ) );
						return false;
					}
					subMenuArrayPtr[ foreachIndex ].second->addMenu( manu );
				}
				node_stack_ptr->subMenus.emplace_back( compVector, manu );
			}
			buff = appendUnity;
			++nameVectorIndex;
		} while( nameVectorIndex < nameVectorCount );
	// 最后的路径
	compVector.emplace_back( nameVectorArratPtr[ nameVectorCount ] );
	foreachCount = node_stack_ptr->actions.size( );
	foreachIndex = 0;
	compVectorArrayCount = compVector.size( );
	compArrayPtr = compVector.data( );
	auto actionArrayPtr = node_stack_ptr->actions.data( );
	for( ; foreachIndex < foreachCount; ++foreachIndex ) {

		leftCount = actionArrayPtr[ foreachIndex ].first.size( );
		if( leftCount != compVectorArrayCount )
			continue;
		leftArray = actionArrayPtr[ foreachIndex ].first.data( );
		for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
			if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
				break;
		if( compVectorIndex == compVectorArrayCount )
			break;
	}
	if( foreachIndex != foreachCount ) {
		QString msg( "[ %1 ]节点菜单对象已经存在对应的 QAction" );
		printerDirector->error( msg.arg( appendUnity ) );
		return false;
	}
	auto action = new QAction( nameVectorArratPtr[ nameVectorCount ] );
	using QActionTriggered = void(QAction::*)( bool );
	QActionTriggered triggered = &QAction::triggered;
	node_stack_ptr->actions.emplace_back( compVector, action );
	if( connectCreateNodeAction( node_stack_ptr, action, triggered, node_type_name, action_click_function ) == false ) {
		QString msg( "[ %1 ]节点菜单对象无法创建对应的 QAction 信号" );
		printerDirector->error( msg.arg( appendUnity ) );
		return false;
	}
	// 路径数量大于 0，则寻找挂靠
	compVectorArrayCount -= 1;
	if( compVectorArrayCount != 0 ) {
		foreachCount = node_stack_ptr->subMenus.size( );
		foreachIndex = 0;
		subMenuArrayPtr = node_stack_ptr->subMenus.data( );
		for( ; foreachIndex < foreachCount; ++foreachIndex ) {
			leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
			if( leftCount != compVectorArrayCount )
				continue;
			leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
			for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
				if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
					break;
			if( compVectorIndex == compVectorArrayCount )
				break;
		}
		if( foreachIndex == foreachCount ) {
			QString msg( "[ %1 ]节点菜单对象不存在挂靠的 QMenu" );
			printerDirector->error( msg.arg( appendUnity ) );
			return false;
		}
		subMenuArrayPtr[ foreachIndex ].second->addAction( action );
	}

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
