#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>
#include <QPainter>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/menu/action/nodeAddAction.h"
#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/tools/tools.h"

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
	} else if( selectNodeWidget && geometry( ).contains( currentMouseInWidgetPos ) )
		selectNodeWidget->move( currentMouseInWidgetPos - selectNodeWidgetOffset );
	repaint( );
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
void NodeGraph::error( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &msg, size_t error_code, size_t error_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << "error( " << error_code << " ) " << error_line;
}
void NodeGraph::finish( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &result_type_object, size_t return_code, size_t over_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << over_line;
}
