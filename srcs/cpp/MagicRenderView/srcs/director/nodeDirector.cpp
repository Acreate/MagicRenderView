#include "nodeDirector.h"
#include <QMenu>

#include <node/stack/nodeStack.h>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"

#include "../node/node/node.h"
#include "../node/nodeInfo/nodePortLinkInfo.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"
#include "../node/stack/baseNodeStack/baseNodeStack.h"

#include "../srack/srackInfo.h"

#include "../tools/path.h"

#include "../widget/drawLinkWidget.h"
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
	mainWindow = instancePtr->getMainWindow( );
	if( mainWindow )
		connect( mainWindow, &MainWindow::release_signal, [this] ( MainWindow *release_ptr ) {
			if( mainWindow == release_ptr )
				mainWindow = nullptr;
		} );
	mainWidget = mainWindow->getMainWidget( );
	if( mainWidget )
		connect( mainWidget, &MainWidget::release_signal, [this] ( MainWidget *release_ptr ) {
			if( mainWidget == release_ptr )
				mainWidget = nullptr;
		} );
	drawNodeWidget = mainWidget->getDrawNodeWidget( );
	if( drawNodeWidget )
		connect( drawNodeWidget, &DrawNodeWidget::release_signal, [this] ( DrawNodeWidget *release_ptr ) {
			if( drawNodeWidget == release_ptr )
				drawNodeWidget = nullptr;
		} );
	drawLinkWidget = mainWidget->getDrawLinkWidget( );
	if( drawLinkWidget )
		connect( drawLinkWidget, &DrawLinkWidget::release_signal, [this] ( DrawLinkWidget *release_ptr ) {
			if( drawLinkWidget == release_ptr )
				drawLinkWidget = nullptr;
		} );
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
			delete pair[ index ];
	}
}
NodeDirector::~NodeDirector( ) {
	releaseResources( );
	if( nodeVarDirector )
		delete nodeVarDirector;
}
Node * NodeDirector::createNode( const QString &node_type_name, MainWidget *main_widget ) {
	if( main_widget == nullptr || node_type_name.isEmpty( ) )
		return nullptr;
	Node *node = nullptr;
	if( node == nullptr )
		return node;
	auto refNdoeInfo = new NodeRefLinkInfo( node );
	if( main_widget->addNode( refNdoeInfo ) == false ) {
		delete node;
		delete refNdoeInfo;
		return node;
	}
	appendRefNodeVectorAtNode( refNdoeInfo );
	connectNodeSignals( node );
	return node;
}
bool NodeDirector::linkPort( OutputPort *output_port, InputPort *input_port ) {

	NodeRefLinkInfo *outputNodeRef = output_port->parentNode->nodeRefLinkInfoPtr;
	NodeRefLinkInfo *inputNodeRef = input_port->parentNode->nodeRefLinkInfoPtr;

	if( outputNodeRef->hasLinkInfo( output_port, input_port ) == true )
		return true;
	NodeEnum::PortType inType = input_port->getPortType( );
	if( inType != NodeEnum::PortType::Any ) {
		NodeEnum::PortType outType = output_port->getPortType( );
		if( outType != inType )
			return false;
		QString outVarTypeName = output_port->getVarTypeName( );
		QString inVarTypeName = input_port->getVarTypeName( );
		if( outVarTypeName != inVarTypeName )
			return false;
	}
	bool appendInputRef = inputNodeRef->appendInputRef( output_port, outputNodeRef, input_port );
	return appendInputRef;
}
void NodeDirector::drawLinkLines( QPainter &draw_link_widget ) {
	size_t count = refNodeVector.size( );
	auto arrayPtr = refNodeVector.data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		size_t linkPortCount = arrayPtr[ index ]->nodePortLinkInfo->inputPortVector.size( );
		auto linkPortArray = arrayPtr[ index ]->nodePortLinkInfo->inputPortVector.data( );
		size_t linkPortIndex;
		for( linkPortIndex = 0; linkPortIndex < linkPortCount; ++linkPortIndex ) {
			auto point = linkPortArray[ linkPortIndex ].first->getLinkPoint( );
			auto startPoint = linkPortArray[ linkPortIndex ].first->parentNode->nodeRefLinkInfoPtr->drawNodeWidget->mapFromGlobal( point );

			size_t linkTargetPortCount = linkPortArray[ linkPortIndex ].second.size( );
			auto linkTargetPortArray = linkPortArray[ linkPortIndex ].second.data( );
			size_t linkTargetPortIndex;
			for( linkTargetPortIndex = 0; linkTargetPortIndex < linkTargetPortCount; ++linkTargetPortIndex ) {
				point = linkTargetPortArray[ linkTargetPortIndex ]->getLinkPoint( );
				auto endPoint = linkPortArray[ linkPortIndex ].first->parentNode->nodeRefLinkInfoPtr->drawNodeWidget->mapFromGlobal( point );
				draw_link_widget.drawLine( startPoint, endPoint );
			}
		}
	}
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

		if( mainWindow == nullptr ) {
			mainWindow = instancePtr->getMainWindow( );
			if( mainWindow == nullptr ) {
				auto errorMsg = tr( "无法匹配主窗口[Application::]getMainWindow( )" );
				printerDirector->error( errorMsg );
				emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
				delete node;
				return;
			}
			connect( mainWindow, &MainWindow::release_signal, [this] ( MainWindow *release_ptr ) {
				if( mainWindow == release_ptr )
					mainWindow = nullptr;
			} );
		}
		if( mainWidget == nullptr ) {
			mainWidget = mainWindow->getMainWidget( );
			if( mainWidget == nullptr ) {
				auto errorMsg = tr( "无法匹配主渲染组件[MainWindow::getMainWidget()]" );
				printerDirector->error( errorMsg );
				emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWidget_Nullptr, errorMsg, Create_SrackInfo( ) );
				delete node;
				return;
			}

			connect( mainWidget, &MainWidget::release_signal, [this] ( MainWidget *release_ptr ) {
				if( mainWidget == release_ptr )
					mainWidget = nullptr;
			} );

		}
		auto refNdoeInfo = new NodeRefLinkInfo( node );
		if( mainWidget->addNode( refNdoeInfo ) == false ) {
			auto errorMsg = tr( "节点添加失败[DrawNodeWidget::addNode( Node *add_node )]" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Add, errorMsg, Create_SrackInfo( ) );
			delete refNdoeInfo;
			delete node;
			return;
		}
		if( drawNodeWidget == nullptr ) {
			drawNodeWidget = mainWidget->getDrawNodeWidget( );
			if( drawNodeWidget == nullptr ) {
				auto errorMsg = tr( "无法匹配节点渲染组件 [MainWidget::getDrawNodeWidget()]" );
				emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Nullptr, errorMsg, Create_SrackInfo( ) );
				delete node;
				return;
			}
			connect( drawNodeWidget, &DrawNodeWidget::release_signal, [this] ( DrawNodeWidget *release_ptr ) {
				if( drawNodeWidget == release_ptr )
					drawNodeWidget = nullptr;
			} );
		}
		if( drawLinkWidget == nullptr ) {
			drawLinkWidget = mainWidget->getDrawLinkWidget( );
			if( drawNodeWidget == nullptr ) {
				auto errorMsg = tr( "无法匹配节点连接组件 [MainWidget::getDrawLinkWidget()]" );
				emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Nullptr, errorMsg, Create_SrackInfo( ) );
				delete node;
				return;
			}
			connect( drawLinkWidget, &DrawLinkWidget::release_signal, [this] ( DrawLinkWidget *release_ptr ) {
				if( drawLinkWidget == release_ptr )
					drawLinkWidget = nullptr;
			} );
		}
		if( node->parent( ) != drawNodeWidget ) {
			auto errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
			delete refNdoeInfo;
			delete node;
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
		appendRefNodeVectorAtNode( refNdoeInfo );
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
		if( data[ index ]->getCurrentNode( ) == remove_node ) {
			NodeRefLinkInfo *nodeRefLinkInfo = data[ index ];
			refNodeVector.erase( refNodeVector.begin( ) + index );
			delete nodeRefLinkInfo;
			if( drawNodeWidget )
				drawNodeWidget->update( );
			if( drawLinkWidget )
				drawLinkWidget->update( );
			break;
		}
}
void NodeDirector::appendRefNodeVectorAtNode( NodeRefLinkInfo *append_node_ref_link_info ) {
	size_t count = refNodeVector.size( );
	auto data = refNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == append_node_ref_link_info )
			return;

	if( index == count )
		refNodeVector.emplace_back( append_node_ref_link_info );
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
