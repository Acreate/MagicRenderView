#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>
NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	nodeMenu = new NodeAddMenu( this );

	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );
}
NodeGraph::~NodeGraph( ) {
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	Qt::MouseButton mouseButton = event->button( );
	QPoint currentMouseInWidgetPos = event->pos( );
	switch( mouseButton ) {
		case Qt::RightButton : // 使用配置的位置显示菜单
			nodeMenu->move( QCursor::pos( ) );
			nodeMenu->show( );
			break;
		case Qt::LeftButton : // 配置位置
			cursorPos = QCursor::pos( );
			if( mousePosLabel->isHidden( ) ) {
				mousePosLabel->show( );
				mousePosLabel->move( currentMouseInWidgetPos );
			} else if( mousePosLabel->geometry( ).contains( currentMouseInWidgetPos ) ) {
				nodeMenu->move( QCursor::pos( ) );
				nodeMenu->show( );
			} else
				mousePosLabel->move( currentMouseInWidgetPos );

			break;
	}
}
