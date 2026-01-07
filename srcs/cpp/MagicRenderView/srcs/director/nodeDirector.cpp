#include "nodeDirector.h"
#include <QMenu>
#include <QPainter>

#include <node/stack/nodeStack.h>
#include <QLabel>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"
#include "../menu/edit/normalNodeEditorPropertyMenu.h"
#include "../menu/generateNode/normalGenerateNodeMenu.h"
#include "../menuStack/edit/editorNodeMenuStack.h"
#include "../menuStack/generateNode/generateNodeMenuStack.h"

#include "../node/node/node.h"
#include "../node/nodeInfo/nodeHistory.h"
#include "../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/begin/beginNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/generate/intGenerateNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/jump/jumpNodeWidget.h"
#include "../node/nodeRunInfo/nodeRunInfo.h"
#include "../node/nodeType/nodeTypeInfoSerializeion.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"
#include "../node/portLinkType/portLinkType.h"
#include "../node/stack/baseNodeStack/baseNodeStack.h"

#include "../srack/srackInfo.h"

#include "../tools/path.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

#include "../win/mainWindow.h"
#include "menuDirector.h"
constexpr uint64_t maxGenerator = UINT_FAST64_MAX / sizeof( Node );
bool NodeDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	varDirector = instancePtr->getVarDirector( );
	menuDirector = instancePtr->getMenuDirector( );
	appDirector = instancePtr->getAppDirector( );
	releaseObjResources( );
	if( portLink->init( instancePtr, this, varDirector, appDirector ) == false )
		return false;
	QString errorMsg;
	if( initNodeRenderGraphWidget( errorMsg ) == false ) {
		printerDirector->info( errorMsg,Create_SrackInfo( ) );
		return false;
	}

	auto generateNodeMenuStack = menuDirector->getGenerateNodeMenuStack( );
	normalGenerateNodeMenu = generateNodeMenuStack->createGenerateNodeMenu( tr( "常规" ) );
	connect( normalGenerateNodeMenu, &NormalGenerateNodeMenu::create_node_signal, this, &NodeDirector::createNodeSlot );
	EditorNodeMenuStack *editorNodeMenuStack = menuDirector->getEditorNodeMenuStack( );
	normalNodeEditorPropertyMenu = editorNodeMenuStack->createNormalNodeEditorPropertyMenu( tr( "常规" ) );
	if( normalNodeEditorPropertyMenu == nullptr )
		return false;
	oldCreateNode = nullptr;
	connect( normalNodeEditorPropertyMenu, &NormalNodeEditorPropertyMenu::remove_node_action_signal, this, &NodeDirector::removeNodeActionSlot );
	connect( normalNodeEditorPropertyMenu, &NormalNodeEditorPropertyMenu::unLink_signal, this, &NodeDirector::nodeEditorMenuUnLinkSlot );
	connect( normalNodeEditorPropertyMenu, &NormalNodeEditorPropertyMenu::show_node_at_widget_signal, this, &NodeDirector::editorMenuShowNodeAtWidgetSlot );
	connect( normalNodeEditorPropertyMenu, &NormalNodeEditorPropertyMenu::show_node_edit_info_widget_signal, this, &NodeDirector::editorMenuShowEditInfoWidgetSlot );
	return true;
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

NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ), mainWindow( nullptr ), mainWidget( nullptr ), varDirector( nullptr ), currentShowWidget( nullptr ) {
	portLink = new PortLinkType;
	normalGenerateNodeMenu = nullptr;
	normalNodeEditorPropertyMenu = nullptr;
}
QString NodeDirector::nodeArrayToString( const Node *const *printf_nodes, const size_t &printf_node_count ) {
	if( printf_nodes == nullptr || printf_node_count == 0 ) {
		return "class {  }[0];";
	}
	QStringList nodeToStringList;
	QString outInfo( "class { \n%1 \n\t}[%2];" );
	QString number( "[%2] : %1 = %3 ;" );
	for( size_t index = 0; index < printf_node_count; index += 1 ) {
		auto metaObject = printf_nodes[ index ]->metaObject( );
		auto className = metaObject->className( );
		auto nodeToString = printf_nodes[ index ]->toQString( );
		nodeToStringList.append( number.arg( className ).arg( index ).arg( nodeToString ) );
	}
	return outInfo.arg( nodeToStringList.join( "\n" ) ).arg( printf_node_count );
}
QString NodeDirector::nodeArrayToString( const std::list< Node * > &printf_node_list ) {
	size_t count = printf_node_list.size( );
	auto nodeArrayPtr = new Node *[ count ];
	size_t index = 0;
	auto listConstIterator = printf_node_list.begin( );
	for( ; index < count; ++index )
		nodeArrayPtr[ index ] = *listConstIterator;
	auto resultString = nodeArrayToString( nodeArrayPtr, count );
	delete [] nodeArrayPtr;
	return resultString;
}
void NodeDirector::releaseObjResources( ) {
	releaseMenuResources( );
	releaseNodeResources( );
	releaseNodeInfoWidgetResources( );
	releaseNodeHistoryResources( );
}
void NodeDirector::releaseMenuResources( ) {
	if( normalGenerateNodeMenu )
		delete normalGenerateNodeMenu;
	if( normalNodeEditorPropertyMenu )
		delete normalNodeEditorPropertyMenu;
}
void NodeDirector::releaseNodeResources( ) {
	size_t count;
	size_t index;
	count = nodeArchiveVector.size( );
	for( index = 0; index < count; ++index ) {
		auto iterator = nodeArchiveVector.begin( );
		auto node = *iterator;
		nodeArchiveVector.erase( iterator );
		delete node;
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
	if( portLink )
		delete portLink;
}
Node * NodeDirector::createNode( const QString &node_type_name ) {

	if( node_type_name.isEmpty( ) ) {
		printerDirector->info( tr( "无法创建[]节点" ), Create_SrackInfo( ) );
		return nullptr;
	}
	if( mainWidget == nullptr ) {
		QString error_msg;
		if( initNodeRenderGraphWidget( error_msg ) == false ) {
			printerDirector->info( error_msg, Create_SrackInfo( ) );
			return nullptr;
		}
	}

	auto createNodePtr = normalGenerateNodeMenu->getCreateResultNode( node_type_name );
	if( appendRefNodeVectorAtNode( node_type_name, createNodePtr ) == nullptr ) {
		delete createNodePtr;
		return nullptr;
	}
	
	return createNodePtr;
}
bool NodeDirector::linkPort( OutputPort *output_port, InputPort *input_port ) {
	if( output_port->hasInputPortRef( input_port ) )
		return true;
	if( portLink->linkPort( output_port, input_port ) == false )
		return false;
	input_port->emplaceBackOutputPortRef( output_port );
	if( mainWidget )
		mainWidget->update( );
	return true;
}

bool NodeDirector::disLinkPort( OutputPort *output_port, InputPort *input_port ) {
	return output_port->eraseInputPortRef( input_port );
}

void NodeDirector::drawLinkLines( QPainter &draw_link_widget ) {
	Node *node;
	size_t count;
	Node **arrayPtr;
	size_t index;
	size_t outputPortCount;
	OutputPort **outputPortArray;
	size_t outputPortIndex;
	size_t connectInputPortCount;
	InputPort **connectInputPortArray;
	size_t connectInputPortIndex;
	OutputPort *outputPort;
	InputPort *inputPort;
	QPoint outputPortPos;
	QPoint inputPortPos;
	count = nodeArchiveVector.size( );
	if( count == 0 )
		return;
	arrayPtr = nodeArchiveVector.data( );
	for( index = 0; index < count; ++index ) {
		node = arrayPtr[ index ];
		if( node == nullptr )
			continue;
		outputPortCount = node->outputPortVector.size( );
		outputPortArray = node->outputPortVector.data( );
		outputPortIndex = 0;
		for( ; outputPortIndex < outputPortCount; ++outputPortIndex ) {
			outputPort = outputPortArray[ outputPortIndex ];
			connectInputPortCount = outputPort->refInputPortVector.size( );
			if( connectInputPortCount == 0 )
				continue;
			outputPortPos = outputPort->getLinkPoint( );
			outputPortPos = mainWidget->mapFromGlobal( outputPortPos );

			connectInputPortArray = outputPort->refInputPortVector.data( );
			connectInputPortIndex = 0;
			for( ; connectInputPortIndex < connectInputPortCount; ++connectInputPortIndex ) {
				inputPort = connectInputPortArray[ connectInputPortIndex ];
				inputPortPos = inputPort->getLinkPoint( );
				inputPortPos = mainWidget->mapFromGlobal( inputPortPos );
				draw_link_widget.drawLine( outputPortPos, inputPortPos );
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
bool NodeDirector::initNodeRenderGraphWidget( QString &result_error_msg ) {
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
	NodeTypeInfoSerializeion nodeTypeInfoSerializeion;
	auto node = nodeArchiveVector.data( );
	size_t count = nodeArchiveVector.size( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeTypeInfoSerializeion.appendNodePtr( node[ index ] ) == false ) {
			printerDirector->info( tr( "节点[%1]添加序列失败" ).arg( node[ index ]->toQString( ) ), Create_SrackInfo( ) );
			return false;
		}
	if( nodeTypeInfoSerializeion.toData( result_vector_data ) == false )
		return false;
	return true;
}
bool NodeDirector::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {

	QString error_msg;
	if( initNodeRenderGraphWidget( error_msg ) == false ) {
		printerDirector->info( error_msg, Create_SrackInfo( ) );
		return false;
	}
	// 删除节点
	releaseNodeResources( );

	NodeTypeInfoSerializeion nodeTypeInfoSerializeion;

	auto nodeCreateFunction = [this] ( const QString &node_name, const size_t &node_generator_code, const int32_t &node_x_pos, const int32_t &node_y_pos ) ->Node * {

		auto createNodePtr = createNode( node_name );
		if( createNodePtr == nullptr ) {
			printerDirector->info( tr( "无法创建[%1]节点" ).arg( node_name ), Create_SrackInfo( ) );
			return nullptr;
		}
		createNodePtr->move( node_x_pos, node_y_pos );
		createNodePtr->generateCode = node_generator_code;
		return createNodePtr;
	};
	auto portLinkFcuntion = [this] ( const uint64_t &output_node_generator_code, const uint64_t &output_port_generator_code, const uint64_t &input_node_generator_code, const uint64_t &input_port_generator_code ) ->bool {
		auto outputNode = getNode( output_node_generator_code );
		if( outputNode == nullptr ) {
			printerDirector->info( tr( "无法匹配生成码[%1]的输出节点" ).arg( output_node_generator_code ), Create_SrackInfo( ) );
			return false;
		}
		auto inputNode = getNode( input_node_generator_code );
		if( inputNode == nullptr ) {
			printerDirector->info( tr( "无法匹配生成码[%1]的输入节点" ).arg( input_node_generator_code ), Create_SrackInfo( ) );
			return false;
		}
		auto outputPort = outputNode->getOutputPort( output_port_generator_code );
		if( outputPort == nullptr ) {
			printerDirector->info( tr( "无法匹配生成码[%1]的输出端口" ).arg( output_port_generator_code ), Create_SrackInfo( ) );
			return false;
		}
		auto inputPort = inputNode->getInputPort( input_port_generator_code );
		if( inputPort == nullptr ) {
			printerDirector->info( tr( "无法匹配生成码[%1]的输入端口" ).arg( input_port_generator_code ), Create_SrackInfo( ) );
			return false;
		}
		return linkPort( outputPort, inputPort );
	};
	if( nodeTypeInfoSerializeion.loadData( this, result_use_count, source_array_ptr, source_array_count, nodeCreateFunction, portLinkFcuntion ) == false )
		return false;
	QString errorMsg;
	if( sortArchiveCode( errorMsg ) == false )
		printerDirector->info( errorMsg,Create_SrackInfo( ) );
	return true;
}
QSize NodeDirector::getMaxNodeRenderSize( ) const {
	int x = 0;
	int y = 0;
	size_t count = nodeArchiveVector.size( );
	auto arrayPtr = nodeArchiveVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		Node *currentNode = arrayPtr[ index ];
		int maxPosX = currentNode->width( ) + currentNode->pos( ).x( );
		int maxPosY = currentNode->height( ) + currentNode->pos( ).y( );
		if( maxPosX > x )
			x = maxPosX;
		if( maxPosY > y )
			y = maxPosY;
	}
	return QSize { x, y };
}
NodeRunInfo * NodeDirector::builderCurrentAllNodeAtNodeRunInfo( ) {
	NodeRunInfo *result = new NodeRunInfo( );
	size_t count = nodeArchiveVector.size( );
	if( count != 0 ) {
		auto nodeRefLinkInfoArrayPtr = nodeArchiveVector.data( );
		result->appendBuilderNode( nodeRefLinkInfoArrayPtr, count );
		if( result->builderRunInstance( ) ) {
			connect( result, &NodeRunInfo::clear_signal, this, &NodeDirector::nodeRunInfoClear );
			return result;
		}
	}

	delete result;
	return nullptr;
}
NodeRunInfo * NodeDirector::freeCurrentAllNodeAtNodeRunInfo( NodeRunInfo *node_run_info ) {
	delete node_run_info;
	return nullptr;
}
Node * NodeDirector::getNode( const uint64_t &node_generator_code ) const {
	size_t count = nodeArchiveVector.size( );
	if( count == 0 )
		return nullptr;
	auto nodeArrayPtr = nodeArchiveVector.data( );
	if( nodeArrayPtr[ node_generator_code - 1 ] && nodeArrayPtr[ node_generator_code - 1 ]->generateCode == node_generator_code )
		return nodeArrayPtr[ node_generator_code - 1 ];
	//size_t index = 0;
	//for( ; index < count; ++index )
	//	if( nodeArrayPtr[ index ] != nullptr && nodeArrayPtr[ index ]->generateCode == node_generator_code )
	//		return nodeArrayPtr[ index ];
	return nullptr;
}
bool NodeDirector::popNormalNodeEditorPropertyMenu( const QPoint &pop_pos, Node *node_target ) const {
	if( normalNodeEditorPropertyMenu->setNode( node_target ) == false )
		return false;
	normalNodeEditorPropertyMenu->popup( pop_pos );
	return true;
}
bool NodeDirector::popNormalGenerateNodeMenu( const QPoint &pop_pos ) const {
	if( normalGenerateNodeMenu == nullptr )
		return false;
	normalGenerateNodeMenu->popup( pop_pos );
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
	connect( connect_qaction_ptr, connect_qaction_fun_ptr, [this,action_click_function, node_type_name]( ) {
		QString errorMsg;
		auto node = action_click_function( node_type_name );

		if( appendRefNodeVectorAtNode( node_type_name, node ) == nullptr ) {
			delete node;
			return;
		}
		mainWidget->ensureVisible( node );
		mainWidget->update( );
	} );
	return true;
}

void NodeDirector::removeRefNodeVectorAtNode( Node *remove_node ) {
	size_t count = nodeArchiveVector.size( );
	auto data = nodeArchiveVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == remove_node ) {
			data[ index ] = nullptr;
			break;
		}
}
Node * NodeDirector::appendRefNodeVectorAtNode( const QString &append_node_name, Node *append_node ) {
	QString errorMsg;
	if( append_node == nullptr ) {
		errorMsg = tr( "节点 (%1) 为 nullptr" );
		printerDirector->error( errorMsg.arg( append_node_name ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, append_node_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
		return nullptr;
	}

	if( mainWidget->addNode( append_node ) == false ) {
		errorMsg = tr( "节点 (%1) [Node::init( MainWidget *parent )] 的初始化函数运行失败" );
		printerDirector->error( errorMsg.arg( append_node_name ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, append_node_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
		return nullptr;
	}
	if( appendNodeToArchiveVector( append_node ) == false ) {
		errorMsg = tr( "节点 (%1) [NodeDirector::updateNodeGeneratorCode( Node *update_generate_code )] 无法分配生成码" );
		printerDirector->error( errorMsg.arg( append_node_name ), Create_SrackInfo( ) );
		emit error_create_node_signal( this, append_node_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg, Create_SrackInfo( ) );
		return nullptr;
	}

	QPoint fromGlobal = mainWidget->mapFromGlobal( normalGenerateNodeMenu->pos( ) );
	if( fromGlobal.x( ) < 0 )
		fromGlobal.setX( 0 );
	if( fromGlobal.y( ) < 0 )
		fromGlobal.setY( 0 );
	append_node->move( fromGlobal );
	if( oldCreateNode )
		oldCreateNode->setNodeStyle( NodeEnum::NodeStyleType::None );
	oldCreateNode = append_node;
	oldCreateNode->setNodeStyle( NodeEnum::NodeStyleType::Create );
	append_node->show( );
	mainWidget->ensureVisible( append_node );
	finishCreateNode( append_node );

	auto currentHistory = [append_node, this] {
		auto node = createNode( append_node->nodeTitleName );
		auto mapFromGlobal = mainWidget->mapFromGlobal( QCursor::pos( ) );
		node->move( mapFromGlobal );
		if( mainWidget )
			mainWidget->update( );
		return nullptr;
	};
	auto cancelHistory = [append_node, this] {
		delete append_node;
		return nullptr;
	};
	appendHistorIndexEnd( currentHistory, cancelHistory );
	return append_node;
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
bool NodeDirector::appendNodeToArchiveVector( Node *update_generate_code ) {
	size_t count = nodeArchiveVector.size( );

	if( count == 0 ) {
		update_generate_code->generateCode = 1;
		nodeArchiveVector.emplace_back( update_generate_code );
		return true;
	}
	auto nodeArrayPtr = nodeArchiveVector.data( );
	size_t index;
	update_generate_code->generateCode = 0;
	for( index = 0; index < count; ++index )
		if( nodeArrayPtr[ index ] == nullptr ) {
			update_generate_code->generateCode = index + 1;
			nodeArrayPtr[ index ] = update_generate_code;
			return true;
		}
	if( maxGenerator == count ) // 最大生成号
		return false;
	update_generate_code->generateCode = count + 1;
	nodeArchiveVector.emplace_back( update_generate_code );
	return true;
}
bool NodeDirector::sortArchiveCode( QString &error_msg ) {
	size_t count = nodeArchiveVector.size( );
	auto nodeArrayPtr = nodeArchiveVector.data( );
	uint64_t maxCode = 0;
	size_t index = 0;
	for( ; index < count; ++index )
		if( maxCode < nodeArrayPtr[ index ]->generateCode )
			maxCode = nodeArrayPtr[ index ]->generateCode;
	if( maxGenerator < maxCode ) {
		// 最大生成号
		error_msg = tr( "超出可控数量" );
		return false;
	}
	decltype(nodeArchiveVector) buff( maxCode, nullptr );
	auto destArrayPtr = buff.data( );
	for( index = 0; index < maxCode; ++index )
		destArrayPtr[ nodeArrayPtr[ index ]->generateCode - 1 ] = nodeArrayPtr[ index ];
	nodeArchiveVector = buff;
	return true;
}
void NodeDirector::releaseNode( Node *release_node, const SrackInfo &srack_info ) {
	//printerDirector->info( "节点释放", Create_SrackInfo( ) );
	if( release_node == oldCreateNode )
		oldCreateNode = nullptr;
	appendHistorIndexEnd(
		[] {
			return nullptr;
		}, [] { // todo :撤销删除（创建对象）
			return nullptr;
		} );
	removeRefNodeVectorAtNode( release_node );
	emit release_node_signal( this, release_node, srack_info );
}
void NodeDirector::errorRunNode( Node *error_node, const SrackInfo &org_srack_info, NodeEnum::ErrorType error_type, const QString &error_msg ) {
	//printerDirector->info( "节点错误", Create_SrackInfo( ) );
	emit error_run_node_signal( this, Create_SrackInfo( ), error_node, org_srack_info, error_type, error_msg );
}
void NodeDirector::adviseRunNode( Node *advise_node, const SrackInfo &org_srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg ) {
	//printerDirector->info( "节点建议", Create_SrackInfo( ) );
	emit advise_run_node_signal( this, Create_SrackInfo( ), advise_node, org_srack_info, advise_type, advise_msg );
}
void NodeDirector::finishRunNode( Node *finish_node, const SrackInfo &org_srack_info ) {
	//printerDirector->info( "节点运行完成", Create_SrackInfo( ) );
	emit finish_run_node_signal( this,Create_SrackInfo( ), finish_node, org_srack_info );
}

void NodeDirector::nodeRunInfoClear( NodeRunInfo *clear_obj, const SrackInfo &srack_info ) {
	emit node_run_info_clear_signal( this, Create_SrackInfo( ), clear_obj, srack_info );
	//delete clear_obj;
}
void NodeDirector::createNodeSlot( NormalGenerateNodeMenu *signal_obj_ptr, QAction *create_item, const QString &create_node_name, const NormalGenerateNodeMenuType::TCreateNodeFunction &create_node_function ) {
	auto nodeName = create_item->text( );
	Node *nodePtr = create_node_function( nodeName );
	if( appendRefNodeVectorAtNode( nodeName, nodePtr ) == nullptr ) {
		delete nodePtr;
		return;
	}
}
void NodeDirector::nodeEditorMenuUnLinkSlot( NormalNodeEditorPropertyMenu *signal_ptr, OutputPort *output_port, InputPort *input_port ) {
	//printerDirector->info( tr( "编辑菜单发出断开信号" ), Create_SrackInfo( ) );
	disLinkPort( output_port, input_port );
	mainWidget->update( );
}
void NodeDirector::removeNodeActionSlot( NormalNodeEditorPropertyMenu *signal_ptr, Node *remove_target ) {
	if( remove_target == nullptr )
		return;
	size_t count = nodeArchiveVector.size( );
	auto data = nodeArchiveVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == remove_target )
			break;
	if( index != count )
		delete remove_target;
}
void NodeDirector::editorMenuShowEditInfoWidgetSlot( NormalNodeEditorPropertyMenu *signal_ptr, Node *show_node, NodeInfoWidget *show_info_widget ) {
	//printerDirector->info( tr( "编辑菜单发出信息菜单显示信号" ), Create_SrackInfo( ) );
	if( show_info_widget->initNodeInfo( show_node ) )
		show_info_widget->show( );
}
void NodeDirector::editorMenuShowNodeAtWidgetSlot( NormalNodeEditorPropertyMenu *signal_ptr, Node *ensure_node ) {
	//printerDirector->info( tr( "编辑菜单发出主窗口显示节点信号" ), Create_SrackInfo( ) );
	mainWidget->ensureVisible( ensure_node );
}
void NodeDirector::finishCreateNode( Node *finish_node ) {

	connect( finish_node, &Node::connect_ref_input_port_node_signal, this, &NodeDirector::connectRefInputPortNodeSlot );
	connect( finish_node, &Node::dis_connect_ref_input_port_node_signal, this, &NodeDirector::disConnectRefInputPortNodeSlot );
	connect( finish_node, &Node::connect_ref_output_port_node_signal, this, &NodeDirector::connectRefOutputPortNodeSlot );
	connect( finish_node, &Node::dis_connect_ref_output_port_node_signal, this, &NodeDirector::disConnectRefOutputPortNodeSlot );

	connect( finish_node, &Node::connect_input_port_signal, this, &NodeDirector::connectInputPortSlot );
	connect( finish_node, &Node::dis_connect_input_port_signal, this, &NodeDirector::disConnectInputPortSlot );
	connect( finish_node, &Node::connect_output_port_signal, this, &NodeDirector::connectOutputPortSlot );
	connect( finish_node, &Node::dis_connect_output_port_signal, this, &NodeDirector::disConnectOutputPortSlot );

	connect( finish_node, &Node::release_node_signal, this, &NodeDirector::releaseNode );
	connect( finish_node, &Node::advise_run_node_signal, this, &NodeDirector::adviseRunNode );
	connect( finish_node, &Node::error_run_node_signal, this, &NodeDirector::errorRunNode );
	connect( finish_node, &Node::finish_run_node_signal, this, &NodeDirector::finishRunNode );
	emit finish_create_node_signal( this, finish_node, Create_SrackInfo( ) );
}
void NodeDirector::connectRefInputPortNodeSlot( Node *output_port_node, Node *ref_input_port_node ) {
	//printerDirector->info( "节点产生引用", Create_SrackInfo( ) );
	if( currentShowWidget && currentShowWidget->isHidden( ) == false )
		currentShowWidget->newNodeRefLinkInfo( ref_input_port_node, output_port_node );
	emit connect_ref_input_port_node_signal( this, output_port_node, ref_input_port_node );
}
void NodeDirector::disConnectRefInputPortNodeSlot( Node *output_port, Node *ref_input_port ) {
	//printerDirector->info( "端口释放链接", Create_SrackInfo( ) );
	emit dis_connect_ref_input_port_node_signal( this, output_port, output_port );
}
void NodeDirector::connectRefOutputPortNodeSlot( Node *input_port_node, Node *ref_output_port ) {
	//printerDirector->info( "节点产生引用", Create_SrackInfo( ) );
	emit connect_ref_output_port_node_signal( this, input_port_node, ref_output_port );
}
void NodeDirector::disConnectRefOutputPortNodeSlot( Node *input_port_node, Node *ref_output_port ) {
	//printerDirector->info( "端口释放链接", Create_SrackInfo( ) );
	emit dis_connect_ref_output_port_node_signal( this, input_port_node, ref_output_port );
}
void NodeDirector::connectOutputPortSlot( OutputPort *output_port, InputPort *ref_input_port ) {
	//printerDirector->info( "端口产生链接", Create_SrackInfo( ) );
	emit connect_output_port_signal( this, output_port, ref_input_port );
}
void NodeDirector::disConnectOutputPortSlot( OutputPort *output_port, InputPort *ref_input_port ) {
}
void NodeDirector::connectInputPortSlot( InputPort *input_port, OutputPort *ref_output_port ) {
	//printerDirector->info( "端口产生链接", Create_SrackInfo( ) );
	emit connect_input_port_signal( this, input_port, ref_output_port );
}
void NodeDirector::disConnectInputPortSlot( InputPort *input_port, OutputPort *ref_output_port ) {
}
