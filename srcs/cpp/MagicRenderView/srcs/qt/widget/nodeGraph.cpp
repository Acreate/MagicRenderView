#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/menu/action/nodeAddAction.h"
#include "qt/tools/tools.h"
NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	nodeMenu = new NodeAddMenu( this );
	// todo : 创建需要的节点，并且绘制到该窗口当中 
	connect( nodeMenu, &NodeAddMenu::activeNodeAction, [this] ( const NodeAddAction *node_add_action ) ->void {
		auto functionDeclaration = node_add_action->getFunctionDeclaration( ).get( );
		if( functionDeclaration == nullptr )
			return;
		tools::debug::printError( functionDeclaration->getFunctionDeclarationName( ) );
	} );
	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );
	setMouseTracking( true );
	mouseEventStatus = MouseEventType::Init;
}
NodeGraph::~NodeGraph( ) {
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	switch( mouseEventStatus ) {
		/// 左键菜单
		case MouseEventType::Press : {
			// 鼠标按键
			Qt::MouseButton mouseButton = event->button( );
			// 鼠标全局位置
			QPoint cursorPos = QCursor::pos( );
			// 鼠标窗口位置
			QPoint currentMouseInWidgetPos = event->pos( );
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
	mouseEventStatus = MouseEventType::Press;
}
