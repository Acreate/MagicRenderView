#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/menu/action/nodeAddAction.h"
#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/tools/tools.h"
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
		auto generateNode = instance->generateNode( functionName );
		if( generateNode ) {
			generateNode->move( currentMouseInWidgetPos );
			generateNode->setParent( this );
			generateNode->connectNodeGraphWidget( this );
			generateNode->show( );
		} else
			tools::debug::printError( functionName );
	} );
	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );
}
NodeGraph::~NodeGraph( ) {
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	switch( mouseEventStatus ) {
		/// 左键菜单
		case MouseEventType::Press : {
			if( selectNodeComponent == nullptr && selectNodeWidget == nullptr ) {
				// 鼠标按键
				Qt::MouseButton mouseButton = event->button( );
				cursorPos = QCursor::pos( );
				currentMouseInWidgetPos = event->pos( );
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
				return;
			}
			break;
		}
	}
	mouseEventStatus = MouseEventType::Release;
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
}
void NodeGraph::mouseMoveEvent( QMouseEvent *event ) {
	mouseEventStatus = MouseEventType::Move;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	if( selectNodeComponent == nullptr && selectNodeWidget && geometry( ).contains( currentMouseInWidgetPos ) )
		selectNodeWidget->move( currentMouseInWidgetPos - selectNodeWidgetOffset );
}
void NodeGraph::mousePressEvent( QMouseEvent *event ) {
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	mouseEventStatus = MouseEventType::Press;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	auto childrenList = children( );
	QRect geometry;
	INodeWidget *nodeWidget;
	for( auto child : childrenList ) {
		nodeWidget = qobject_cast< INodeWidget * >( child );
		if( nodeWidget ) {
			selectNodeWidgetOffset = event->pos( );
			geometry = nodeWidget->geometry( );
			if( geometry.contains( selectNodeWidgetOffset ) == false )
				continue;
			selectNodeWidget = nodeWidget;
			selectNodeWidgetOffset = selectNodeWidgetOffset - nodeWidget->pos( );
			selectNodeComponent = nodeWidget->getPosNodeComponent( selectNodeWidgetOffset );
			return;
		}
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
