#include "nodeDirector.h"
#include <QMenu>
#include <QPainter>

#include <node/stack/nodeStack.h>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"

#include "../node/node/node.h"
#include "../node/nodeInfo/inputportLinkOutputPortInfo.h"
#include "../node/nodeInfo/nodeHistory.h"
#include "../node/nodeInfo/nodePortLinkActionPair.h"
#include "../node/nodeInfo/nodePortLinkInfo.h"
#include "../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/begin/beginNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/generate/intGenerateNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/jump/jumpNodeWidget.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"
#include "../node/stack/baseNodeStack/baseNodeStack.h"

#include "../srack/srackInfo.h"

#include "../tools/path.h"
#include "../widget/drawHighlightWidget.h"

#include "../widget/drawLinkWidget.h"
#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

#include "../win/mainWindow.h"

bool NodeDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	varDirector = instancePtr->getVarDirector( );
	releaseObjResources( );
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
			printerDirector->error( msg.arg( className ), Create_SrackInfo( ) );
			for( index = 0; index < count; ++index )
				delete nodeStackArrayPtr[ index ];
			nodeStacks.clear( );
			return false;
		}
	// 初始化菜单
	std::list< std::pair< QString, QAction * > > actionMap;
	for( index = 0; index < count; ++index ) {
		QMenu *generateCreateMenu = fromNodeGenerateCreateMenu( nodeStackArrayPtr[ index ], actionMap );
		if( generateCreateMenu == nullptr )
			continue;
		if( connectNodeAction( nodeStackArrayPtr[ index ], actionMap ) == false )
			delete generateCreateMenu;
		this->nodeCreateMenu->addMenu( generateCreateMenu );
	}

	QString errorMsg;
	bool drawLinkWidgetIniRsult = initDrawLinkWidget( errorMsg );
	if( drawLinkWidgetIniRsult == false )
		printerDirector->info( errorMsg,Create_SrackInfo( ) );
	if( drawLinkWidget )
		drawLinkWidget->update( );
	if( drawNodeWidget )
		drawNodeWidget->update( );
	if( drawHighlightWidget )
		drawHighlightWidget->update( );
	return drawLinkWidgetIniRsult;
}
bool NodeDirector::showNodeWidgeInfo( Node *association_node ) {
	if( association_node == nullptr ) {
		if( currentShowWidget )
			currentShowWidget->hide( );
		return false;
	}
	if( currentShowWidget && currentShowWidget->isNodeTypeInfoWidget( association_node ) == true ) {
		currentShowWidget->releaseVar( );
		currentShowWidget->clearVarPtr( );
		if( currentShowWidget->initNodeInfo( association_node ) )
			return true;
		currentShowWidget->hide( );
		return false;
	}
	auto nodeInfoWidget = getNodeWidgeInfo( association_node );

	if( nodeInfoWidget != nullptr && nodeInfoWidget->isNodeTypeInfoWidget( association_node ) == true ) {
		if( currentShowWidget )
			currentShowWidget->hide( );
		if( nodeInfoWidget->initNodeInfo( association_node ) == false )
			return false;
		nodeInfoWidget->show( );
		return true;
	}
	return false;
}
NodeInfoWidget * NodeDirector::getNodeWidgeInfo( Node *association_node ) {
	if( association_node == nullptr )
		return nullptr;
	size_t count = nodeInfoWidgets.size( );
	auto arrayPtr = nodeInfoWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isNodeTypeInfoWidget( association_node ) == true )
			return arrayPtr[ index ];
	return nullptr;
}

NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ), mainWindow( nullptr ), mainWidget( nullptr ), drawNodeWidget( nullptr ), drawHighlightWidget( nullptr ), drawLinkWidget( nullptr ), varDirector( nullptr ), currentShowWidget( nullptr ) {
	nodeVarDirector = new VarDirector;
	nodeCreateMenu = new QMenu;
}
void NodeDirector::releaseObjResources( ) {
	releaseMenuResources( );
	releaseNodeResources( );
	releaseNodeInfoWidgetResources( );
	releaseNodeHistoryResources( );
}
void NodeDirector::releaseMenuResources( ) {
	size_t count;
	size_t index;

	count = nodeStacks.size( );
	if( count ) {
		auto nodeStackArrayPtr = nodeStacks.data( );
		for( index = 0; index < count; ++index )
			delete nodeStackArrayPtr[ index ];
		nodeStacks.clear( );
	}
	nodeCreateMenu->clear( );
}
void NodeDirector::releaseNodeResources( ) {
	size_t count;
	size_t index;
	count = linkActionMap.size( );
	if( count != 0 ) {
		auto buff = linkActionMap;
		linkActionMap.clear( );
		auto pair = buff.data( );
		for( index = 0; index < count; ++index )
			delete pair[ index ];
	}
	count = refNodeVector.size( );
	if( count != 0 ) {
		auto buff = refNodeVector;
		refNodeVector.clear( );
		auto pair = buff.data( );
		for( index = 0; index < count; ++index )
			pair[ index ]->clearInfo( );
		for( index = 0; index < count; ++index ) {
			Node *currentNode = pair[ index ]->currentNode;
			delete pair[ index ];
			delete currentNode;
		}
	}
}
void NodeDirector::releaseNodeInfoWidgetResources( ) {
	auto buff = nodeInfoWidgets;
	nodeInfoWidgets.clear( );
	size_t count = buff.size( );
	auto nodeInfoWidgetArrayPtr = buff.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete nodeInfoWidgetArrayPtr[ index ];
	currentShowWidget = nullptr;
}
void NodeDirector::releaseNodeHistoryResources( ) {
	size_t count = nodeHistorys.size( );
	auto nodenodeHistorysArrayPtr = nodeHistorys.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete nodenodeHistorysArrayPtr[ index ];
	nodeHistoryIndex = 0;
	nodeHistorys.clear( );
}
NodeDirector::~NodeDirector( ) {
	releaseObjResources( );
	if( nodeCreateMenu )
		delete nodeCreateMenu;
	if( nodeVarDirector )
		delete nodeVarDirector;
}
Node * NodeDirector::createNode( const QString &node_type_name, MainWidget *main_widget ) {
	if( main_widget == nullptr || node_type_name.isEmpty( ) )
		return nullptr;
	Node *node = nullptr;
	size_t count = createNodeVector.size( );
	auto createArrayPtr = createNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( createArrayPtr[ index ].first == node_type_name ) {
			node = createArrayPtr[ index ].second( node_type_name );
			break;
		}
	if( node == nullptr ) {
		auto errorMsg = tr( "无法匹配对应的节点名称[%1]" );
		printerDirector->error( errorMsg.arg( node_type_name ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
		return node;
	}
	auto refNdoeInfo = new NodeRefLinkInfo( node );
	if( main_widget->addNode( refNdoeInfo ) == false ) {
		auto errorMsg = tr( "节点的初始化失败[%1]" );
		printerDirector->error( errorMsg.arg( node_type_name ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
		delete node;
		delete refNdoeInfo;
		return nullptr;
	}
	if( node->parent( ) != drawNodeWidget ) {
		auto errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
		printerDirector->error( errorMsg, Create_SrackInfo( ) );
		emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
		delete refNdoeInfo;
		delete node;
		return nullptr;
	}
	if( node->updateLayout( ) == false ) {
		auto errorMsg = tr( "节点布局更新失败[%1::updateLayout()]" );
		printerDirector->error( errorMsg.arg( node->metaObject( )->className( ) ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
		delete node;
		delete refNdoeInfo;
		return nullptr;
	}
	appendRefNodeVectorAtNode( refNdoeInfo );
	node->show( );
	return node;
}
bool NodeDirector::linkPort( OutputPort *output_port, InputPort *input_port ) {

	NodeRefLinkInfo *inputNodeRef = output_port->parentNode->nodeRefLinkInfoPtr;
	NodeRefLinkInfo *outputNodeRef = input_port->parentNode->nodeRefLinkInfoPtr;
	if( inputNodeRef->hasInputRefNode( outputNodeRef ) )
		return false;
	if( inputNodeRef->hasPortRef( input_port, output_port ) == true )
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
	bool appendInputRef = outputNodeRef->appendInputRef( input_port, output_port );
	if( appendInputRef == false )
		return false;
	if( drawLinkWidget )
		drawLinkWidget->update( );
	auto currentHistort = [input_port, output_port, this]( ) {
		linkPort( output_port, input_port );
		if( drawLinkWidget )
			drawLinkWidget->update( );
		return nullptr;
	};
	auto cancelHistort = [this, output_port, input_port]( ) {
		disLinkPort( output_port, input_port );
		if( drawLinkWidget )
			drawLinkWidget->update( );
		return nullptr;
	};
	appendHistorIndexEnd( currentHistort, cancelHistort );

	return appendInputRef;
}
bool NodeDirector::disLinkPort( OutputPort *output_port, InputPort *input_port ) {
	auto inputParentNode = input_port->parentNode;
	if( inputParentNode == nullptr )
		return true;
	NodeRefLinkInfo *inputNodeRef = inputParentNode->nodeRefLinkInfoPtr;
	if( inputNodeRef == nullptr )
		return true;
	if( inputNodeRef->hasPortRef( input_port, output_port ) == false )
		return true;
	bool removeInputRef = inputNodeRef->removeInputRef( input_port, output_port );
	if( removeInputRef == false )
		return removeInputRef;
	return removeInputRef;
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
			InputPort *inputPort = linkPortArray[ linkPortIndex ]->getInputPort( );
			auto point = inputPort->getLinkPoint( );
			auto startPoint = inputPort->parentNode->nodeRefLinkInfoPtr->drawNodeWidget->mapFromGlobal( point );

			auto &outputPortVector = linkPortArray[ linkPortIndex ]->getOutputPortVector( );
			size_t linkTargetPortCount = outputPortVector.size( );
			auto linkTargetPortArray = outputPortVector.data( );
			size_t linkTargetPortIndex;
			for( linkTargetPortIndex = 0; linkTargetPortIndex < linkTargetPortCount; ++linkTargetPortIndex ) {
				point = linkTargetPortArray[ linkTargetPortIndex ]->getLinkPoint( );
				auto endPoint = inputPort->parentNode->nodeRefLinkInfoPtr->drawNodeWidget->mapFromGlobal( point );
				draw_link_widget.drawLine( startPoint, endPoint );
			}
		}
	}
}
bool NodeDirector::cancelNodeHistory( ) {
	if( nodeHistoryIndex == 0 )
		return false;
	nodeHistoryIndex -= 1;
	NodeHistory *nodeHistory = nodeHistorys.data( )[ nodeHistoryIndex ];
	auto callCancelOperate = nodeHistory->callCancelOperate( );
	if( callCancelOperate == nullptr )
		return false;
	delete callCancelOperate;
	return true;
}
bool NodeDirector::initDrawLinkWidget( QString &result_error_msg ) {
	if( mainWindow == nullptr ) {
		mainWindow = instancePtr->getMainWindow( );
		if( mainWindow == nullptr ) {
			result_error_msg = tr( "获取主要窗口失败 [Application::getMainWindow( )]" );
			return false;
		}
		connect( mainWindow, &MainWindow::release_signal, [this] ( MainWindow *release_ptr ) {
			if( mainWindow == release_ptr )
				mainWindow = nullptr;
		} );
	}
	if( mainWidget == nullptr ) {
		mainWidget = mainWindow->getMainWidget( );
		if( mainWidget == nullptr ) {
			result_error_msg = tr( "获取节点窗口失败 [MainWindow::getMainWidget( )]" );
			return false;
		}
		connect( mainWidget, &MainWidget::release_signal, [this] ( MainWidget *release_ptr ) {
			if( mainWidget == release_ptr )
				mainWidget = nullptr;
		} );
	}
	if( drawNodeWidget == nullptr ) {
		drawNodeWidget = mainWidget->getDrawNodeWidget( );
		if( drawNodeWidget == nullptr ) {
			result_error_msg = tr( "获取节点渲染窗口失败 [MainWidget::getDrawNodeWidget( )]" );
			return false;
		}
		connect( drawNodeWidget, &DrawNodeWidget::release_signal, [this] ( DrawNodeWidget *release_ptr ) {
			if( drawNodeWidget == release_ptr )
				drawNodeWidget = nullptr;
		} );
	}
	if( drawLinkWidget == nullptr ) {
		drawLinkWidget = mainWidget->getDrawLinkWidget( );
		if( drawNodeWidget == nullptr ) {
			result_error_msg = tr( "获取连接渲染窗口失败 [MainWidget::getDrawNodeWidget( )]" );
			return false;
		}
		connect( drawLinkWidget, &DrawLinkWidget::release_signal, [this] ( DrawLinkWidget *release_ptr ) {
			if( drawLinkWidget == release_ptr )
				drawLinkWidget = nullptr;
		} );
	}
	if( drawHighlightWidget == nullptr ) {
		drawHighlightWidget = mainWidget->getDrawHighlightWidget( );
		if( drawNodeWidget == nullptr ) {
			result_error_msg = tr( "获取连接渲染窗口失败 [MainWidget::getDrawHighlightWidget( )]" );
			return false;
		}
		connect( drawHighlightWidget, &DrawHighlightWidget::release_signal, [this] ( DrawHighlightWidget *release_ptr ) {
			if( drawHighlightWidget == release_ptr )
				drawHighlightWidget = nullptr;
		} );
	}
	return initNodeInfoWidget( result_error_msg );
}
bool NodeDirector::initNodeInfoWidget( QString &result_error_msg ) {
	if( mainWindow == nullptr ) {
		result_error_msg = tr( "缺少主配置窗口，使用 [Application::getMainWindow( )] 获取" );
		return false;
	}
	appendNodeInfoWidget( new JumpNodeWidget( mainWindow ) );
	appendNodeInfoWidget( new IntGenerateNodeWidget( mainWindow ) );
	appendNodeInfoWidget( new BeginNodeWidget( mainWindow ) );
	return true;
}
bool NodeDirector::findNodeInputPort( InputPort *&result_input_port_ptr, const uint64_t &node_id_key, const QString &input_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count ) {
	size_t index = 0;
	for( ; index < source_count; ++index )
		if( source_data[ index ].first == node_id_key ) {
			result_input_port_ptr = source_data[ index ].second->getInputPort( input_port_name );
			if( result_input_port_ptr != nullptr )
				return true;
			return false;
		}
	return false;
}
bool NodeDirector::findNodeOutputPort( OutputPort *&result_output_port_ptr, const uint64_t &node_id_key, const QString &output_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count ) {
	size_t index = 0;
	for( ; index < source_count; ++index )
		if( source_data[ index ].first == node_id_key ) {
			result_output_port_ptr = source_data[ index ].second->getOutputPort( output_port_name );
			if( result_output_port_ptr != nullptr )
				return true;
			return false;
		}
	return false;
}
bool NodeDirector::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	int32_t *int32Ptr = nullptr;
	QString *stringPtr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( int32Ptr ) == false )
		return false;
	if( varDirector.create( stringPtr ) == false )
		return false;
	std::vector< uint8_t > vectorInfo;
	std::vector< uint8_t > converResult;
	size_t refNodeArrayCount = refNodeVector.size( );
	auto refNodeArrayPtr = refNodeVector.data( );
	size_t refNodeArrayIndex = 0;
	// 序列化节点个数
	*uint64Ptr = refNodeArrayCount;
	if( varDirector.toVector( uint64Ptr, converResult ) == false )
		return false;
	vectorInfo.append_range( converResult );
	for( ; refNodeArrayIndex < refNodeArrayCount; ++refNodeArrayIndex ) {
		// 节点
		Node *currentNode = refNodeArrayPtr[ refNodeArrayIndex ]->currentNode;
		// 名称
		*stringPtr = currentNode->nodeName;
		if( varDirector.toVector( stringPtr, converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
		// x 坐标
		*int32Ptr = currentNode->x( );
		if( varDirector.toVector( int32Ptr, converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
		// y 坐标
		*int32Ptr = currentNode->y( );
		if( varDirector.toVector( int32Ptr, converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
		// id
		*uint64Ptr = ( uint64_t ) currentNode;
		if( varDirector.toVector( uint64Ptr, converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
		// 节点数据
		if( currentNode->toUint8VectorData( converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
		// 连接信息
		if( refNodeArrayPtr[ refNodeArrayIndex ]->nodePortLinkInfo->toUint8VectorData( converResult ) == false )
			return false;
		vectorInfo.append_range( converResult );
	}
	*uint64Ptr = vectorInfo.size( );
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	result_vector_data.append_range( vectorInfo );
	return true;
}
bool NodeDirector::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {

	QString error_msg;
	if( initDrawLinkWidget( error_msg ) == false ) {
		printerDirector->info( error_msg, Create_SrackInfo( ) );
		return false;
	}

	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	int32_t *int32Ptr = nullptr;
	QString *stringPtr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( int32Ptr ) == false )
		return false;
	if( varDirector.create( stringPtr ) == false )
		return false;
	// 总数判定
	void *anyPtr = uint64Ptr;
	if( varDirector.toVar( result_use_count, source_array_ptr, source_array_count, anyPtr ) == false )
		return false;
	auto mod = source_array_count - result_use_count;
	if( mod < *uint64Ptr )
		return false;
	auto offset = source_array_ptr + result_use_count;
	// 总数
	if( varDirector.toVar( result_use_count, offset, mod, anyPtr ) == false )
		return false;
	mod = mod - result_use_count;
	offset = offset + result_use_count;
	size_t count = *uint64Ptr;
	size_t index = 0;
	std::vector< std::vector< InputportLinkOutputPortInfoMap > > resultMapVector;
	std::vector< std::pair< size_t, Node * > > nodeIdPair;
	resultMapVector.resize( count );
	nodeIdPair.resize( count );
	auto pairArrayPtr = resultMapVector.data( );
	auto nodeIdPairArrayPtr = nodeIdPair.data( );
	NodePortLinkInfo temp( nullptr );
	QPoint pos;
	releaseNodeResources( );
	for( ; index < count; ++index ) {
		// 节点名称
		anyPtr = stringPtr;
		if( varDirector.toVar( result_use_count, offset, mod, anyPtr ) == false )
			return false;
		mod = mod - result_use_count;
		offset = offset + result_use_count;
		// x
		anyPtr = int32Ptr;
		if( varDirector.toVar( result_use_count, offset, mod, anyPtr ) == false )
			return false;
		pos.setX( *int32Ptr );
		mod = mod - result_use_count;
		offset = offset + result_use_count;
		// y
		anyPtr = int32Ptr;
		if( varDirector.toVar( result_use_count, offset, mod, anyPtr ) == false )
			return false;
		pos.setY( *int32Ptr );
		mod = mod - result_use_count;
		offset = offset + result_use_count;
		// id
		anyPtr = uint64Ptr;
		if( varDirector.toVar( result_use_count, offset, mod, anyPtr ) == false )
			return false;
		mod = mod - result_use_count;
		offset = offset + result_use_count;
		// 节点创建
		auto node = createNode( *stringPtr, mainWidget );
		if( node == nullptr )
			return false;
		node->move( pos );
		// 节点数据
		if( node->formUint8ArrayData( result_use_count, offset, mod ) == false )
			return false;
		mod = mod - result_use_count;
		offset = offset + result_use_count;
		// 保存节点地址映射
		nodeIdPairArrayPtr[ index ] = std::pair< uint64_t, Node * >( *uint64Ptr, node );
		// 连接信息
		if( temp.toLinkMap( pairArrayPtr[ index ], result_use_count, offset, mod ) == false )
			return false;
		mod = mod - result_use_count;
		offset = offset + result_use_count;
	}

	std::pair< std::pair< unsigned long long, QString >, std::vector< std::pair< unsigned long long, QString > > > *linkArrayPtr;
	size_t linkArrayCount;
	size_t linkArrayIndex;
	for( index = 0; index < count; ++index ) {
		linkArrayPtr = pairArrayPtr[ index ].data( );
		linkArrayCount = pairArrayPtr[ index ].size( );
		for( linkArrayIndex = 0; linkArrayIndex < linkArrayCount; ++linkArrayIndex ) {
			auto id = linkArrayPtr[ linkArrayIndex ].first.first;
			InputPort *inputPort = nullptr;
			OutputPort *outputPort = nullptr;
			if( findNodeInputPort( inputPort, id, linkArrayPtr[ linkArrayIndex ].first.second, nodeIdPairArrayPtr, count ) == false )
				return false;
			size_t outCount = linkArrayPtr[ linkArrayIndex ].second.size( );
			auto outArrayPtr = linkArrayPtr[ linkArrayIndex ].second.data( );
			size_t outIndex;
			for( outIndex = 0; outIndex < outCount; ++outIndex ) {
				id = outArrayPtr[ outIndex ].first;

				if( findNodeOutputPort( outputPort, id, outArrayPtr[ outIndex ].second, nodeIdPairArrayPtr, count ) == false )
					return false;
				if( linkPort( outputPort, inputPort ) == false )
					return false;
			}

		}
	}
	mainWidget->calculateNodeRenderSize( );
	result_use_count = offset - source_array_ptr;
	return true;
}
QSize NodeDirector::getMaxNodeRenderSize( ) const {
	int x = 0;
	int y = 0;
	size_t count = refNodeVector.size( );
	auto arrayPtr = refNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		Node *currentNode = arrayPtr[ index ]->currentNode;
		int maxPosX = currentNode->width( ) + currentNode->pos( ).x( );
		int maxPosY = currentNode->height( ) + currentNode->pos( ).y( );
		if( maxPosX > x )
			x = maxPosX;
		if( maxPosY > y )
			y = maxPosY;
	}
	return QSize { x, y };
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
		QString errorMsg;
		auto node = action_click_function( node_type_name );
		if( node == nullptr ) {
			errorMsg = tr( "无法匹配 [%1::%1(const QString& node_name)] 节点的创建函数" );
			printerDirector->error( errorMsg.arg( node_type_name ), Create_SrackInfo( ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
			return;
		}
		if( drawLinkWidget == nullptr )
			if( initDrawLinkWidget( errorMsg ) == false ) {
				printerDirector->error( errorMsg, Create_SrackInfo( ) );
				emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
				delete node;
				return;
			}
		auto refNdoeInfo = new NodeRefLinkInfo( node );
		if( mainWidget->addNode( refNdoeInfo ) == false ) {
			errorMsg = tr( "节点添加失败[DrawNodeWidget::addNode( Node *add_node )]" );
			printerDirector->error( errorMsg, Create_SrackInfo( ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::DrawNodeWidget_Add, errorMsg, Create_SrackInfo( ) );
			delete refNdoeInfo;
			delete node;
			return;
		}
		if( node->parent( ) != drawNodeWidget ) {
			errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
			printerDirector->error( errorMsg, Create_SrackInfo( ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
			delete refNdoeInfo;
			delete node;
			return;
		}
		if( node->updateLayout( ) == false ) {
			errorMsg = tr( "节点布局更新失败[%1::updateLayout()]" );
			printerDirector->error( errorMsg.arg( node->metaObject( )->className( ) ), Create_SrackInfo( ) );
			emit error_create_node_signal( this, node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg, Create_SrackInfo( ) );
			delete node;
			delete refNdoeInfo;
			return;
		}
		appendRefNodeVectorAtNode( refNdoeInfo );
		node->show( );
		mainWidget->ensureVisible( node );
		mainWidget->update( );
	} );
	return true;
}

void NodeDirector::removeRefNodeVectorAtNode( Node *remove_node ) {
	size_t count = refNodeVector.size( );
	auto data = refNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->getCurrentNode( ) == remove_node ) {
			NodeRefLinkInfo *nodeRefLinkInfo = data[ index ];
			refNodeVector.erase( refNodeVector.begin( ) + index );

			//auto inputPorts = nodeRefLinkInfo->currentNode->getInputPortVector( );
			//auto inputPortArray = inputPorts.data( );
			//count = inputPorts.size( );
			//for( index = 0; index < count; ++index )
			//	removePortLinkAction( inputPortArray[ index ] );

			//auto outputPorts = nodeRefLinkInfo->currentNode->getOutputPortVector( );
			//auto outputPortArray = outputPorts.data( );
			//count = outputPorts.size( );
			//for( index = 0; index < count; ++index )
			//	removePortLinkAction( outputPortArray[ index ] );

			//count = refNodeVector.size( );
			//data = refNodeVector.data( );
			//for( ; index < count; ++index );
			delete nodeRefLinkInfo;
			if( drawNodeWidget )
				drawNodeWidget->update( );
			if( drawLinkWidget )
				drawLinkWidget->update( );
			if( drawHighlightWidget )
				drawHighlightWidget->update( );
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
	refNodeVector.emplace_back( append_node_ref_link_info );
	finishCreateNode( append_node_ref_link_info );
	append_node_ref_link_info->currentNode->setStyleType( NodeEnum::NodeStyleType::Create );

	auto currentHistory = [append_node_ref_link_info, this] {
		auto node = createNode( append_node_ref_link_info->currentNode->nodeName, mainWidget );
		auto mapFromGlobal = drawNodeWidget->mapFromGlobal( QCursor::pos( ) );
		node->move( mapFromGlobal );
		if( drawNodeWidget )
			drawNodeWidget->update( );
		return nullptr;
	};
	auto cancelHistory = [append_node_ref_link_info, this] {
		delete append_node_ref_link_info->currentNode;
		if( drawNodeWidget )
			drawNodeWidget->update( );
		return nullptr;
	};
	appendHistorIndexEnd( currentHistory, cancelHistory );
}
size_t NodeDirector::removePortLinkAction( InputPort *input_port ) {
	size_t result = 0;
	size_t count = linkActionMap.size( );
	if( count == 0 )
		return result;
	size_t endSize = count;
	auto data = linkActionMap.data( );
	size_t index = 0;
	for( ; index < endSize; ++index )
		if( data[ index ]->inputPort == input_port ) {
			auto nodePortLinkActionPair = data[ index ];
			endSize -= 1;
			data[ index ] = data[ endSize ];
			data[ endSize ] = nullptr;
			delete nodePortLinkActionPair;
			result += 1;
			index -= 1;
		}
	if( endSize != count )
		linkActionMap.resize( endSize );
	return result;
}
size_t NodeDirector::removePortLinkAction( OutputPort *output_port ) {
	size_t result = 0;
	size_t count = linkActionMap.size( );
	if( count == 0 )
		return result;
	size_t endSize = count;
	auto data = linkActionMap.data( );
	size_t index = 0;
	for( ; index < endSize; ++index )
		if( data[ index ]->outputPort == output_port ) {
			auto nodePortLinkActionPair = data[ index ];
			endSize -= 1;
			data[ index ] = data[ endSize ];
			data[ endSize ] = nullptr;
			delete nodePortLinkActionPair;
			result += 1;
			index -= 1;
		}
	if( endSize != count )
		linkActionMap.resize( endSize );
	if( drawNodeWidget )
		drawNodeWidget->update( );
	if( drawLinkWidget )
		drawLinkWidget->update( );
	if( drawHighlightWidget )
		drawHighlightWidget->update( );
	return result;
}
size_t NodeDirector::removePortLinkAction( InputPort *input_port, OutputPort *output_port ) {
	size_t result = 0;
	size_t count = linkActionMap.size( );
	auto data = linkActionMap.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port && data[ index ]->outputPort == output_port ) {
			auto nodePortLinkActionPair = data[ index ];
			linkActionMap.erase( linkActionMap.begin( ) + index );
			delete nodePortLinkActionPair;
			return 1;
		}
	return result;
}
size_t NodeDirector::addEndPortLinkAction( InputPort *input_port, OutputPort *output_port, QAction *input_port_link_action, QAction *output_port_link_action ) {
	size_t result = 0;
	size_t count = linkActionMap.size( );
	auto data = linkActionMap.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port && data[ index ]->outputPort == output_port )
			return result;
	result += 1;
	NodePortLinkActionPair *linkActionPair = new NodePortLinkActionPair( input_port, input_port_link_action, output_port, output_port_link_action );
	linkActionMap.emplace_back( linkActionPair );
	auto releasePair = [this, linkActionPair]( ) {
		size_t linkActionMapCount = linkActionMap.size( );
		auto linkActionMapArrayPtr = linkActionMap.data( );
		size_t linkActionMapIndex = 0;
		for( ; linkActionMapIndex < linkActionMapCount; ++linkActionMapIndex )
			if( linkActionMapArrayPtr[ linkActionMapIndex ] == linkActionPair ) {
				delete linkActionPair;
				linkActionMap.erase( linkActionMap.begin( ) + linkActionMapIndex );
				return;
			}
	};
	connect( input_port->parentNode, &Node::release_node_signal, releasePair );
	connect( output_port->parentNode, &Node::release_node_signal, releasePair );
	return result;
}
bool NodeDirector::appendNodeInfoWidget( NodeInfoWidget *append_node_info_widget_ptr ) {
	nodeInfoWidgets.emplace_back( append_node_info_widget_ptr );
	connect( append_node_info_widget_ptr, &NodeInfoWidget::release_signal, [this] ( NodeInfoWidget *release_ptr ) {
		size_t count = nodeInfoWidgets.size( );
		auto nodeInfoWidgetArrayPtr = nodeInfoWidgets.data( );
		for( size_t index = 0; index < count; ++index )
			if( nodeInfoWidgetArrayPtr[ index ] == release_ptr ) {
				if( release_ptr == currentShowWidget )
					currentShowWidget = nullptr; // 释放的窗口需要配置为 nullptr
				nodeInfoWidgets.erase( nodeInfoWidgets.begin( ) + index );
				return;
			}
	} );
	connect( append_node_info_widget_ptr, &NodeInfoWidget::show_signal, [ this] ( NodeInfoWidget *show_ptr ) {
		currentShowWidget = show_ptr;
	} );
	connect( append_node_info_widget_ptr, &NodeInfoWidget::hide_signal, [ this] ( NodeInfoWidget *hid_ptr ) {
		if( hid_ptr == currentShowWidget )
			currentShowWidget = nullptr;
	} );
	connect( append_node_info_widget_ptr, &NodeInfoWidget::ok_signal, [ this] ( NodeInfoWidget *send_signal_ptr, EditorNodeInfoScrollArea *data_change_widget ) {

	} );
	connect( append_node_info_widget_ptr, &NodeInfoWidget::cancel_signal, [ this] ( NodeInfoWidget *send_signal_ptr, EditorNodeInfoScrollArea *data_change_widget ) {

	} );
	return true;
}
void NodeDirector::removeHistorIndexEnd( ) {
	size_t count = nodeHistorys.size( );
	if( nodeHistoryIndex == count )
		return;
	auto nodeHistoryArrayPtr = nodeHistorys.data( );
	size_t index = nodeHistoryIndex;
	for( ; index < count; ++index )
		delete nodeHistoryArrayPtr[ index ];
	nodeHistorys.resize( nodeHistoryIndex );
}
void NodeDirector::appendHistorIndexEnd( const std::function< NodeHistory*( ) > &current_history, const std::function< NodeHistory*( ) > &cancel_history ) {
	removeHistorIndexEnd( );
	auto newHistrort = new NodeHistory( current_history, cancel_history );
	nodeHistorys.emplace_back( newHistrort );
	nodeHistoryIndex = nodeHistorys.size( );
}
void NodeDirector::releaseNode( Node *release_node, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点释放", Create_SrackInfo( ) );

	if( currentShowWidget && currentShowWidget->isHidden( ) == false )
		currentShowWidget->removeCurrentRefNodeInfo( release_node->nodeRefLinkInfoPtr );
	appendHistorIndexEnd(
		[] {
			return nullptr;
		}, [] { // todo :撤销删除（创建对象）
			return nullptr;
		} );
	removeRefNodeVectorAtNode( release_node );
	emit release_node_signal( this, release_node, srack_info );
}
void NodeDirector::errorRunNode( Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点错误", Create_SrackInfo( ) );
	emit error_run_node_signal( this, error_node, error_type, error_msg, srack_info );
}
void NodeDirector::adviseRunNode( Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点建议", Create_SrackInfo( ) );
	emit advise_run_node_signal( this, advise_node, advise_type, advise_msg, srack_info );
}
void NodeDirector::finishRunNode( Node *finish_node, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点运行完成", Create_SrackInfo( ) );
	emit finish_run_node_signal( this, finish_node, srack_info );
}

void NodeDirector::releaseNodeLink( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *release_output_node_ref_obj_ptr, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点释放引用", Create_SrackInfo( ) );
	if( currentShowWidget && currentShowWidget->isHidden( ) == false )
		currentShowWidget->removeRefNodeRefLinkInfo( signal_obj_ptr, release_output_node_ref_obj_ptr );

	emit finish_release_ref_node_signal( this, signal_obj_ptr->currentNode, release_output_node_ref_obj_ptr->currentNode, srack_info );
}
void NodeDirector::createNodeLink( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *create_output_node_ref_obj_ptr, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点产生引用", Create_SrackInfo( ) );
	if( currentShowWidget && currentShowWidget->isHidden( ) == false )
		currentShowWidget->newNodeRefLinkInfo( signal_obj_ptr, create_output_node_ref_obj_ptr );
	emit finish_create_ref_node_signal( this, signal_obj_ptr->currentNode, create_output_node_ref_obj_ptr->currentNode, srack_info );
}
void NodeDirector::releasePortLink( InputPort *input_port, OutputPort *release_output_port, const SrackInfo &srack_info ) {
	//printerDirector->info( "端口释放链接", Create_SrackInfo( ) );
	emit finish_release_port_link_signal( this, input_port, release_output_port, srack_info );
}
void NodeDirector::createPortLink( InputPort *input_port, OutputPort *bind_output_port, const SrackInfo &srack_info ) {
	//printerDirector->info( "端口产生链接", Create_SrackInfo( ) );

	QString actionText( tr( "断开 [%1.%2] -> [%3.%4] 连接" ) );
	actionText = actionText.arg( bind_output_port->parentNode->nodeName ).arg( bind_output_port->portName ).arg( input_port->parentNode->nodeName ).arg( input_port->portName );
	auto outAction = bind_output_port->disLinkMenu->addAction( actionText );
	auto inAction = input_port->disLinkMenu->addAction( actionText );
	auto disLink = [this, bind_output_port, input_port]( ) {
		if( disLinkPort( bind_output_port, input_port ) == false )
			return;
		removePortLinkAction( input_port, bind_output_port );
		if( drawLinkWidget )
			drawLinkWidget->update( );
		if( drawNodeWidget )
			drawNodeWidget->update( );
		if( drawHighlightWidget )
			drawHighlightWidget->update( );
	};

	connect( outAction, &QAction::triggered, disLink );
	connect( inAction, &QAction::triggered, disLink );
	addEndPortLinkAction( input_port, bind_output_port, inAction, outAction );
	emit finish_create_port_link_signal( this, input_port, bind_output_port, srack_info );
}
void NodeDirector::finishCreateNode( NodeRefLinkInfo *finish_node ) {
	connect( finish_node, &NodeRefLinkInfo::create_node_link_signal, this, &NodeDirector::createNodeLink );
	connect( finish_node, &NodeRefLinkInfo::release_node_link_signal, this, &NodeDirector::releaseNodeLink );
	connect( finish_node, &NodeRefLinkInfo::release_port_link_signal, this, &NodeDirector::releasePortLink );
	connect( finish_node, &NodeRefLinkInfo::create_port_link_signal, this, &NodeDirector::createPortLink );
	connect( finish_node->currentNode, &Node::release_node_signal, this, &NodeDirector::releaseNode );
	connect( finish_node->currentNode, &Node::advise_run_node_signal, this, &NodeDirector::adviseRunNode );
	connect( finish_node->currentNode, &Node::error_run_node_signal, this, &NodeDirector::errorRunNode );
	connect( finish_node->currentNode, &Node::finish_run_node_signal, this, &NodeDirector::finishRunNode );
	emit finish_create_node_signal( this, finish_node->currentNode, Create_SrackInfo( ) );
}
