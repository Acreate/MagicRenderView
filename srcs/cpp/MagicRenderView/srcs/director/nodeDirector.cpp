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

#include "../srack/srackInfo.h"

#include "../tools/path.h"

#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

#include "../win/mainWindow.h"

bool NodeDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	varDirector = instancePtr->getVarDirector( );
	releaseResources( );
	if( nodeVarDirector )
		delete nodeVarDirector;
	nodeVarDirector = new VarDirector;
	if( nodeVarDirector->init( ) == false )
		return false;
	createNodeVector.clear( );

	size_t count;
	size_t index;
	NodeStack **nodeStackArrayPtr;

	// 这里加入节点窗口创建函数
	nodeStacks.emplace_back( new BaseNodeStack( ) );

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
	std::list< std::pair< QString, QAction * > > actionMap;
	for( index = 0; index < count; ++index ) {
		QMenu *generateCreateMenu = fromNodeGenerateCreateMenu( nodeStackArrayPtr[ index ], actionMap );
		if( generateCreateMenu == nullptr )
			continue;
		if( connectNodeAction( nodeStackArrayPtr[ index ], actionMap ) == false )
			delete generateCreateMenu;
		this->nodeCreateMenu->addMenu( generateCreateMenu );
	}
	return true;
}
void NodeDirector::releaseLink( InputPort *signal_port, OutputPort *target_prot ) {

}
void NodeDirector::createLink( InputPort *signal_port, OutputPort *target_prot ) {

}
NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ), nodeCreateMenu( nullptr ), nodeVarDirector( nullptr ) {

}
void NodeDirector::releaseResources( ) {
	size_t count = nodeStacks.size( );
	size_t index;
	if( count ) {
		auto nodeStackArrayPtr = nodeStacks.data( );
		for( index = 0; index < count; ++index )
			delete nodeStackArrayPtr[ index ];
		nodeStacks.clear( );
	}
	if( nodeCreateMenu )
		delete nodeCreateMenu;
	nodeCreateMenu = nullptr;

	count = refNodeVector.size( );
	if( count != 0 ) {
		auto buff = refNodeVector;
		refNodeVector.clear( );
		auto pair = buff.data( );
		for( index = 0; index < count; ++index )
			if( pair[ index ] == nullptr )
				break;
			else {
				delete pair[ index ]->second;
				delete pair[ index ];
			}
	}
}
NodeDirector::~NodeDirector( ) {
	releaseResources( );
	if( nodeVarDirector )
		delete nodeVarDirector;

}
Node * NodeDirector::createNode( const QString &node_type_name, DrawNodeWidget *draw_node_widget ) {
	if( draw_node_widget == nullptr || node_type_name.isEmpty( ) )
		return nullptr;
	Node *node = nullptr;
	if( node == nullptr )
		return node;
	auto refNdoeInfo = new NodeRefLinkInfo;
	if( draw_node_widget->addNode( node, refNdoeInfo ) == false ) {
		delete node;
		delete refNdoeInfo;
		return node;
	}
	appendRefNodeVectorAtNode( node, refNdoeInfo );
	connectNodeSignals( node );
	return node;
}
NodeClickInfo * NodeDirector::getNodeAtPos( const QPoint &point ) {
	return nullptr;
}
QMenu * NodeDirector::fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr, std::list< std::pair< QString, QAction * > > &result_action_map ) {
	auto nodeStackName = node_stack_ptr->objectName( );
	size_t count = node_stack_ptr->nodeGenerate.size( );
	auto data = node_stack_ptr->nodeGenerate.data( );
	size_t index = 0;
	path::pathTree pathTree( nodeStackName );
	for( ; index < count; ++index )
		pathTree.appSubPath( data[ index ].first );
	if( pathTree.getSubPath( ).size( ) == 0 )
		return nullptr;
	result_action_map.clear( );
	nodeStackName = pathTree.getName( );
	QMenu *resultMenu = new QMenu( nodeStackName );
	fromPathTreeGenerateCreateaAction( &pathTree, resultMenu, result_action_map );
	return resultMenu;
}
bool NodeDirector::fromPathTreeGenerateCreateaAction( path::pathTree *path_tree, QMenu *parent_menu, std::list< std::pair< QString, QAction * > > &result_action_map ) {
	auto pathTreeSubPath = path_tree->getSubPath( );
	size_t subPathCount = pathTreeSubPath.size( );
	if( subPathCount == 0 )
		return false;

	auto pathTreeSubPathTree = pathTreeSubPath.data( );
	size_t subPathIndex = 0;
	QString name;
	QAction *addAction;
	std::list< path::pathTree * > subPathTree;
	for( ; subPathIndex < subPathCount; ++subPathIndex )
		if( pathTreeSubPathTree[ subPathIndex ]->getSubPath( ).size( ) == 0 ) {
			name = pathTreeSubPathTree[ subPathIndex ]->getName( );
			addAction = parent_menu->addAction( name );
			pathTreeSubPathTree[ subPathIndex ]->getAbsolutePath( name );
			result_action_map.emplace_back( name, addAction );
		} else
			subPathTree.emplace_back( pathTreeSubPathTree[ subPathIndex ] );
	for( auto &forreachPathTree : subPathTree ) {
		name = forreachPathTree->getName( );
		auto topMenu = parent_menu->addMenu( name );
		NodeDirector::fromPathTreeGenerateCreateaAction( forreachPathTree, topMenu, result_action_map );
	}
	return true;
}

bool NodeDirector::connectNodeAction( NodeStack *node_stack_ptr, const std::list< std::pair< QString, QAction * > > &action_map ) {
	auto rootName = node_stack_ptr->objectName( );
	auto nodeGenerate = node_stack_ptr->nodeGenerate;
	size_t count = nodeGenerate.size( );
	auto data = nodeGenerate.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		data[ index ].first = rootName + '/' + data[ index ].first;

	for( auto &[ findName, actionPtr ] : action_map ) {
		for( index = 0; index < count; ++index )
			if( data[ index ].first == findName )
				break;
		if( index == count )
			return false;
		if( connectCreateNodeAction( node_stack_ptr, actionPtr, &QAction::triggered, findName, data[ index ].second ) == false )
			return false;
	}
	return true;
}
bool NodeDirector::connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( const QString & ) > &action_click_function ) {
	if( connect_qaction_ptr == nullptr || connect_qaction_fun_ptr == nullptr )
		return false;
	createNodeVector.emplace_back( node_type_name, action_click_function );
	connect( connect_qaction_ptr, connect_qaction_fun_ptr, [this,action_click_function, node_type_name]( ) {
		auto node = action_click_function( node_type_name );
		if( node == nullptr ) {
			auto errorMsg = tr( "无法匹配 [%1::%1(const QString& node_name)] 节点的创建函数" );
			printerDirector->error( errorMsg.arg( node_type_name ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
			return;
		}
		MainWindow *mainWindow = instancePtr->getMainWindow( );
		if( mainWindow == nullptr ) {
			auto errorMsg = tr( "无法匹配主窗口[Application::]getMainWindow( )" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
			delete node;
			return;
		}
		MainWidget *mainWidget = mainWindow->getMainWidget( );
		if( mainWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配主渲染组件[MainWindow::getMainWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWidget_Nullptr, errorMsg, Create_SrackInfo( ) );
			delete node;
			return;
		}
		DrawNodeWidget *drawNodeWidget = mainWidget->getDrawNodeWidget( );
		if( drawNodeWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配节点渲染组件 [MainWidget::getDrawNodeWidget()]" );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Nullptr, errorMsg, Create_SrackInfo( ) );
			delete node;
			return;
		}
		auto refNdoeInfo = new NodeRefLinkInfo;
		if( drawNodeWidget->addNode( node, refNdoeInfo ) == false ) {
			auto errorMsg = tr( "节点添加失败[DrawNodeWidget::addNode( Node *add_node )]" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Add, errorMsg, Create_SrackInfo( ) );
			delete node;
			delete refNdoeInfo;
			return;
		}
		if( node->parent( ) != drawNodeWidget ) {
			auto errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
			delete node;
			delete refNdoeInfo;
			return;
		}
		if( node->updateLayout( ) == false ) {
			auto errorMsg = tr( "节点布局更新失败[%1::updateLayout()]" );
			printerDirector->error( errorMsg.arg( node->metaObject( )->className( ) ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
			delete node;
			delete refNdoeInfo;
			return;
		}
		appendRefNodeVectorAtNode( node, refNdoeInfo );
		connectNodeSignals( node );
		node->show( );
		mainWidget->ensureVisible( node );
	} );
	return true;
}
void NodeDirector::connectNodeSignals( Node *connect_obj_ptr ) {
	connect( connect_obj_ptr, &Node::release_node_signal, this, &NodeDirector::releaseNode );
	connect( connect_obj_ptr, &Node::advise_run_node_signal, this, &NodeDirector::adviseRunNode );
	connect( connect_obj_ptr, &Node::error_run_node_signal, this, &NodeDirector::errorRunNode );
	connect( connect_obj_ptr, &Node::finish_run_node_signal, this, &NodeDirector::finishRunNode );
}
void NodeDirector::removeRefNodeVectorAtNode( Node *remove_node ) {
	size_t count = refNodeVector.size( );
	auto data = refNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else if( data[ index ]->first == remove_node ) {
			delete data[ index ]->second;
			if( remove_node->nodeRefLinkInfoPtr == data[ index ]->second )
				remove_node->nodeRefLinkInfoPtr = nullptr;
			index += 1;
			for( ; index < count; ++index )
				if( data[ index ] == nullptr )
					break;
				else
					data[ index - 1 ] = data[ index ];
			data[ index - 1 ] = nullptr;
			break;
		}
}
void NodeDirector::appendRefNodeVectorAtNode( Node *append_node, NodeRefLinkInfo *append_node_ref_link_info ) {
	auto pair = new std::pair< Node *, NodeRefLinkInfo * >( append_node, append_node_ref_link_info );
	size_t count = refNodeVector.size( );
	auto data = refNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else if( data[ index ]->first == append_node )
			return;

	if( index == count )
		refNodeVector.emplace_back( pair );
	else
		data[ index ] = pair;
}
void NodeDirector::releaseNode( Node *release_node, const SrackInfo &srack_info ) {
	removeRefNodeVectorAtNode( release_node );
	emit release_node_signal( this, release_node, srack_info );
}
void NodeDirector::errorRunNode( Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info ) {
	emit error_run_node_signal( this, error_node, error_type, error_msg, srack_info );
}
void NodeDirector::adviseRunNode( Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info ) {
	emit advise_run_node_signal( this, advise_node, advise_type, advise_msg, srack_info );
}
void NodeDirector::finishRunNode( Node *finish_node, const SrackInfo &srack_info ) {
	emit finish_run_node_signal( this, finish_node, srack_info );
}
