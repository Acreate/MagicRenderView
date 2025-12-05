#include "nodeInfoWidget.h"

#include <qcoreevent.h>

#include <win/mainWindow.h>

#include "../bottomTool/bottomNodeInfoTool.h"

#include "../editNodeInfoScrollArea/editorNodeInfoScrollArea.h"

#include "../title/nodeInfoTitle.h"

NodeInfoWidget::NodeInfoWidget( MainWindow *parent ) : QWidget( parent ), parentMainWindow( parent ), editorNodeInfoScrollArea( nullptr ) {
	hide( );
	titile = new NodeInfoTitle( this );
	buttonWidget = new BottomNodeInfoTool( this );
	connect( buttonWidget, &BottomNodeInfoTool::ok_signal, [this]( ) {
		this->okButtonEvent( );
		emit ok_signal( );
	} );
	connect( buttonWidget, &BottomNodeInfoTool::cancel_signal, [this]( ) {
		this->cancelButtonEvent( );
		emit cancel_signal( );
	} );
	parentMainWindow->installEventFilter( this );
}
NodeInfoWidget::~NodeInfoWidget( ) {
	emit release_signal( this );
	if( editorNodeInfoScrollArea )
		delete editorNodeInfoScrollArea;
}
bool NodeInfoWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	return false;
}
bool NodeInfoWidget::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {
	int parentMainWindowWidth;
	int parentMainWindowHeight;
	int currentWidth;
	bool eventFilter = QWidget::eventFilter( event_obj_ptr, event_type );
	if( isHidden( ) )
		return eventFilter;
	auto type = event_type->type( );
	switch( type ) {
		case QEvent::Resize :
			parentMainWindowWidth = parentMainWindow->width( );
			parentMainWindowHeight = parentMainWindow->height( );
			currentWidth = parentMainWindowWidth / 3;
			move( currentWidth, 0 );
			resize( currentWidth, parentMainWindowHeight );
			show( );
			raise( );
			break;
	}

	return eventFilter;
}
bool NodeInfoWidget::event( QEvent *event ) {
	bool eventResult = QWidget::event( event );
	int parentMainWindowWidth;
	int parentMainWindowHeight;
	int currentWidth;
	auto type = event->type( );
	switch( type ) {
		case QEvent::Show :
			parentMainWindowWidth = parentMainWindow->width( );
			parentMainWindowHeight = parentMainWindow->height( );
			currentWidth = parentMainWindowWidth / 3;
			move( currentWidth, 0 );
			resize( currentWidth, parentMainWindowHeight );
			raise( );
			emit show_signal( this );
			break;
		case QEvent::Hide :
			node = nullptr;
			emit hide_signal( this );
	}
	return eventResult;
}
