#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/menu/action/nodeAddAction.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/tools/tools.h"
NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	nodeMenu = new NodeAddMenu( this );
	nodeMenu->init< BaseNodeStack >( );
	setMouseTracking( true );
	mouseEventStatus = MouseEventType::Init;

	// todo : 创建需要的节点，并且绘制到该窗口当中 
	connect( nodeMenu, &NodeAddMenu::activeNodeAction, [this] ( const NodeAddAction *node_add_action ) ->void {
		auto instance = INodeStack::getInstance< BaseNodeStack >( );
		QString functionName = node_add_action->getFunctionName( );
		auto generateNode = instance->generateNode( functionName );
		if( generateNode ) {
			generateNode->move( currentMouseInWidgetPos );
			generateNode->setParent( this );
			generateNode->connectNodeGraphWidget( this );
			generateNode->show( );
			auto pair = tools::debug::getFunctionName( 1 )[ 0 ];
			qDebug( ) << pair.first << " ( " << pair.second << " ) 创建成功 : " + generateNode->objectName( );
		} else
			tools::debug::printError( functionName );
	} );
	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );

	QLabel *test = new QLabel( this );
	test->setText( "测试仪1" );
	test->move( 0, 0 );
	test->setStyleSheet( "*{background:red;}" );
	test = new QLabel( this );
	test->setText( "测试仪2" );
	test->move( 10, 10 );
	test->setStyleSheet( "*{background:green;}" );
}
NodeGraph::~NodeGraph( ) {
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	switch( mouseEventStatus ) {
		/// 左键菜单
		case MouseEventType::Press : {
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

					break;
			}
			break;
		}
		// todo : 操作被选中的节点 
		case MouseEventType::Move :
			break;
	}
	mouseEventStatus = MouseEventType::Release;
}
void NodeGraph::mouseMoveEvent( QMouseEvent *event ) {
	mouseEventStatus = MouseEventType::Move;
}
void NodeGraph::mousePressEvent( QMouseEvent *event ) {
	QWidget *widget = childAt( event->pos( ) );
	if( widget && widget != mousePosLabel ) {
		widget->raise( );
	} else
		mouseEventStatus = MouseEventType::Press;
}

void NodeGraph::selectNodeComponent( INodeWidget *event_node, QWidget *select_component ) {
	event_node->call( );
}
void NodeGraph::error( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &msg, size_t error_code, size_t error_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << "error( " << error_code << " ) " << error_line;
}
void NodeGraph::finish( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &result_type_object, size_t return_code, size_t over_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << over_line;
}
