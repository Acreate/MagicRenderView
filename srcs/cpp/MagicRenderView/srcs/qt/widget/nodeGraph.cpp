#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>
#include <QPainter>

#include <qt/application/application.h>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/menu/action/nodeAddAction.h"
#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/tools/tools.h"

template< typename TUnity >
size_t randomId( std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr ) {
	auto count = storage_vector.size( );
	if( count == 0 ) {
		storage_vector.emplace_back( request_ui_ptr, 1 );
		return 1;
	}
	auto data = storage_vector.data( );
	size_t max = 0;
	while( max < count )
		if( data[ max ].first == request_ui_ptr )
			return data[ max ].second;
		else
			++max;
	max = 1;
	while( max != 0 )
		if( data[ max ].second == max )
			++max;
		else {
			storage_vector.emplace_back( request_ui_ptr, max );
			return max;
		}
	return 0;
}

template< typename TUnity >
size_t removeId( std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr ) {
	size_t result = 0;
	auto begin = storage_vector.begin( );
	auto end = storage_vector.end( );
	for( ; begin != end; ++begin )
		if( begin->first == request_ui_ptr ) {
			result = begin->second;
			storage_vector.emplace( begin );
			return result;
		}
	return result;
}

template< typename TUnity >
inline static bool getUnitySecond( const std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr, size_t *result_scond ) {
	auto count = storage_vector.size( );
	if( count == 0 )
		return false;
	auto dataPtr = storage_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( dataPtr[ index ].first == request_ui_ptr ) {
			*result_scond = dataPtr[ index ].second;
			return true;
		}
	return false;
}

template< typename TUnity >
inline static bool hasUnity( const TUnity &unity, const std_vector< TUnity > &unity_vector ) {
	auto count = unity_vector.size( );
	if( count == 0 )
		return false;
	auto dataPtr = unity_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( dataPtr[ index ] == unity )
			return true;
	return false;
}

NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	nodeComponentIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeWidgetIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	nodeMenu = new NodeAddMenu( this );
	nodeMenu->init< BaseNodeStack >( );
	setMouseTracking( true );
	mouseEventStatus = MouseEventType::Init;

	connect( nodeMenu, &NodeAddMenu::activeAction, [this] ( QAction *action ) ->void {
		auto instance = INodeStack::getInstance< BaseNodeStack >( );
		QString functionName;
		auto nodeAddAction = qobject_cast< NodeAddAction * >( action );
		if( nodeAddAction )
			functionName = nodeAddAction->getFunctionName( );
		else
			functionName = action->text( );
		auto generateNode = instance->generateNode( functionName ); // 节点生成
		if( generateNode ) {
			generateNode->hide( );
			nodeWidgets.emplace_back( generateNode );
			generateNode->move( currentMouseInWidgetPos );
			generateNode->setParent( this );
			generateNode->connectNodeGraphWidget( this );
			generateNode->show( );
			updateMinSize( );
		} else
			tools::debug::printError( functionName );
	} );
	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );
	Application::setNewNodeGraph( this );
}
NodeGraph::~NodeGraph( ) {
}
bool NodeGraph::findPosNodeInfo( const QPoint &check_pos, INodeWidget **result_node_widget, INodeComponent **result_node_component ) {
	size_t count = nodeWidgets.size( );
	if( count == 0 )
		return false;
	auto nodeWidgetVectDataPtr = nodeWidgets.data( );
	INodeWidget *nodeWidgetPtr;
	QRect geometry;
	for( size_t index = 0; index < count; ++index ) {
		nodeWidgetPtr = nodeWidgetVectDataPtr[ index ];
		geometry = nodeWidgetPtr->geometry( );
		if( geometry.contains( check_pos ) == false )
			continue;
		*result_node_widget = nodeWidgetPtr;
		auto checkPos = check_pos - nodeWidgetPtr->pos( );
		*result_node_component = nodeWidgetPtr->getPosNodeComponent( checkPos );
		return true;
	}
	return false;
}

void NodeGraph::updateMinSize( ) {
	QRect newRect = this->rect( );
	for( auto nodeWidgetPtr : nodeWidgets )
		newRect = newRect.united( nodeWidgetPtr->geometry( ) );
	QSize newSize = newRect.size( );
	setMinimumSize( newSize );
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	switch( mouseEventStatus ) {
		// 在按下之后抬起事件
		case MouseEventType::Press : {
			if( selectNodeComponent == nullptr && selectNodeWidget == nullptr ) {
				// 鼠标按键
				Qt::MouseButton mouseButton = event->button( );

				switch( mouseButton ) {
					case Qt::RightButton : // 使用配置的位置显示菜单
						nodeMenu->move( cursorPos );
						nodeMenu->show( );
						break;
					case Qt::LeftButton : // 配置位置
						if( mousePosLabel->isHidden( ) ) {
							mousePosLabel->show( );
							mousePosLabel->move( currentMouseInWidgetPos );
						} else if( mousePosLabel->geometry( ).contains( currentMouseInWidgetPos ) ) {
							nodeMenu->move( cursorPos );
							nodeMenu->show( );
						} else
							mousePosLabel->move( currentMouseInWidgetPos );
						mousePosLabel->raise( );
						break;
				}
			}
		}
		case MouseEventType::Move :
			if( selectNodeComponent ) {
				NodeLinkItem nodeLinkItem;
				INodeComponent::Channel_Type componentChannel = selectNodeComponent->getComponentChannel( );
				switch( componentChannel ) {
					case INodeComponent::Channel_Type::Normal_Default :
						break;
					case INodeComponent::Channel_Type::Input_Read :
						if( nodeLinkItem.setInput( selectNodeWidget, selectNodeComponent ) && findPosNodeInfo( currentMouseInWidgetPos, &selectNodeWidget, &selectNodeComponent ) && selectNodeComponent && selectNodeWidget->getComponentLinkPos( selectNodeComponent, selectNodeComponentPoint ) && nodeLinkItem.setOutput( selectNodeWidget, selectNodeComponent ) == true && hasUnity( nodeLinkItem, nodeLinkItems ) == false )
							nodeLinkItems.emplace_back( nodeLinkItem );
						break;
					case INodeComponent::Channel_Type::Output_Write :
						if( nodeLinkItem.setOutput( selectNodeWidget, selectNodeComponent ) && findPosNodeInfo( currentMouseInWidgetPos, &selectNodeWidget, &selectNodeComponent ) && selectNodeComponent && selectNodeWidget->getComponentLinkPos( selectNodeComponent, selectNodeComponentPoint ) && nodeLinkItem.setInput( selectNodeWidget, selectNodeComponent ) == true && hasUnity( nodeLinkItem, nodeLinkItems ) == false )
							nodeLinkItems.emplace_back( nodeLinkItem );
						break;
				}
			} else if( selectNodeWidget )
				updateMinSize( );
			break;
	}
	mouseEventStatus = MouseEventType::Release;
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	repaint( );
}
void NodeGraph::mouseMoveEvent( QMouseEvent *event ) {
	mouseEventStatus = MouseEventType::Move;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	if( selectNodeComponent ) {
	} else if( selectNodeWidget && geometry( ).contains( currentMouseInWidgetPos ) ) {
		QPoint point = currentMouseInWidgetPos - selectNodeWidgetOffset;
		point.setX( std::max( 0, point.x( ) ) );
		point.setY( std::max( 0, point.y( ) ) );
		selectNodeWidget->move( point );
	}
	repaint( );
}

int NodeGraph::linkHasUnity( const INodeComponent *unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	int has;
	for( size_t index = 0; index < count; ++index )
		if( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}

int NodeGraph::linkHasUnity( const INodeWidget *unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	int has;
	for( size_t index = 0; index < count; ++index )
		if( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}
int NodeGraph::linkHasInputUnity( const INodeComponent *input_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasInputUnity( const INodeWidget *input_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasOutputUnity( const INodeComponent *output_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasOutputUnity( const INodeWidget *output_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeGraph::linkRemoveFirstInputItem( const INodeComponent *input_unity ) {
	auto iterator = nodeLinkItems.begin( );
	auto end = nodeLinkItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->hasInput( input_unity ) ) {
			nodeLinkItems.erase( iterator );
			return 1;
		}
	return 0;
}
int NodeGraph::linkRemoveFirstInputItem( const INodeComponent *output_unity, const INodeComponent *input_unity ) {
	auto iterator = nodeLinkItems.begin( );
	auto end = nodeLinkItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->hasInput( input_unity ) && iterator->hasOutput( output_unity ) ) {
			nodeLinkItems.erase( iterator );
			return 1;
		}
	return 0;
}
bool NodeGraph::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	return false;
}
size_t NodeGraph::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	return 0;
}
size_t NodeGraph::getNodeCompoentID( INodeComponent *node_component ) const {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	size_t resultID = 0;
	if( ::getUnitySecond( nodeComponentID, node_component, &resultID ) )
		return resultID;
	return 0;
}
size_t NodeGraph::getNodeWidgetID( INodeWidget *node_widget ) const {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	size_t resultID = 0;
	if( ::getUnitySecond( nodeWidgetID, node_widget, &resultID ) )
		return resultID;
	return 0;
}
void NodeGraph::mousePressEvent( QMouseEvent *event ) {
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	mouseEventStatus = MouseEventType::Press;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	QRect geometry;
	for( auto nodeWidget : nodeWidgets ) {
		geometry = nodeWidget->geometry( );
		if( geometry.contains( currentMouseInWidgetPos ) == false )
			continue;
		selectNodeWidget = nodeWidget;
		selectNodeWidgetOffset = currentMouseInWidgetPos - nodeWidget->pos( );
		selectNodeComponent = nodeWidget->getPosNodeComponent( selectNodeWidgetOffset );
		if( selectNodeWidget->getComponentLinkPos( selectNodeComponent, selectNodeComponentPoint ) == false /* 没有找到可链接的组件 */ )
			selectNodeComponent = nullptr;
		else if( selectNodeComponent->getComponentChannel( ) == INodeComponent::Channel_Type::Input_Read && selectNodeComponent->isOverlayMulVar( ) == false && linkHasInputUnity( selectNodeComponent ) != 0 )
			if( linkRemoveFirstInputItem( selectNodeComponent ) != 1 )
				tools::debug::printError( "清除连接组件失败 : " + selectNodeComponent->getNodeComponentName( ) + QString::number( ( size_t ) selectNodeComponent, 16 ) );
		repaint( );
		return;
	}
}
void NodeGraph::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPoint start, end;
	for( auto item : nodeLinkItems )
		if( item.getInputOutputPos( &start, &end ) )
			painter.drawLine( start, end );
	if( selectNodeComponent /* 绘制即时连线 */ ) {
		painter.drawLine( selectNodeComponentPoint, currentMouseInWidgetPos );
	}
}

size_t NodeGraph::randomId( INodeComponent *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	return ::randomId( nodeComponentID, request_ui_ptr );
}
size_t NodeGraph::randomId( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::randomId( nodeWidgetID, request_ui_ptr );
}
size_t NodeGraph::removeId( INodeComponent *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	return ::removeId( nodeComponentID, request_ui_ptr );
}
size_t NodeGraph::removeId( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::removeId( nodeWidgetID, request_ui_ptr );
}
void NodeGraph::error( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &msg, size_t error_code, size_t error_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << "error( " << error_code << " ) " << error_line;
}
void NodeGraph::finish( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &result_type_object, size_t return_code, size_t over_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << over_line;
}
void NodeGraph::requestNodeWidgetID( INodeWidget *request_node_widget_ptr ) {
	size_t id = randomId( request_node_widget_ptr );
	if( id )
		request_node_widget_ptr->show( );
}
void NodeGraph::requestNodeComponentID( INodeComponent *request_node_component_ptr ) {
	size_t id = randomId( request_node_component_ptr );
	if( id )
		request_node_component_ptr->show( );
}
void NodeGraph::destoryNodeWidgetID( INodeWidget *request_node_widget_ptr ) {
	removeId( request_node_widget_ptr );
}
void NodeGraph::destoryNodeComponentID( INodeComponent *request_node_component_ptr ) {
	removeId( request_node_component_ptr );
}
