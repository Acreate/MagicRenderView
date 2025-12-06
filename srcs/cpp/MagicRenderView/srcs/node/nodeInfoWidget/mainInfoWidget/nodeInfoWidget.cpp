#include "nodeInfoWidget.h"

#include <qcoreevent.h>

#include <win/mainWindow.h>

#include "../../../director/varDirector.h"

#include "../bottomTool/bottomNodeInfoTool.h"

#include "../editNodeInfoScrollArea/editorNodeInfoScrollArea.h"

#include "../title/nodeInfoTitle.h"

NodeInfoWidget::NodeInfoWidget( MainWindow *parent ) : QWidget( parent ), parentMainWindow( parent ), editorNodeInfoScrollArea( nullptr ) {
	varDirector = new VarDirector;
	hide( );
	titile = new NodeInfoTitle( this );
	buttonWidget = new BottomNodeInfoTool( this );
	connect( buttonWidget, &BottomNodeInfoTool::ok_signal, [this]( ) {
		this->okButtonEvent( );
		emit ok_signal( this, editorNodeInfoScrollArea );
	} );
	connect( buttonWidget, &BottomNodeInfoTool::cancel_signal, [this]( ) {
		this->cancelButtonEvent( );
		emit cancel_signal( this, editorNodeInfoScrollArea );
	} );
	parentMainWindow->installEventFilter( this );
}
NodeInfoWidget::~NodeInfoWidget( ) {
	emit release_signal( this );
	if( editorNodeInfoScrollArea )
		delete editorNodeInfoScrollArea;
	delete varDirector;
}
bool NodeInfoWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	return false;
}
bool NodeInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( editorNodeInfoScrollArea && editorNodeInfoScrollArea->initNode( check_node_ptr ) == false )
		return false;
	return varDirector->init( );
}
QString NodeInfoWidget::getTitleText( ) const {
	return titile->getTitleText( );
}
void NodeInfoWidget::showNodeInfoWidget( const WidgetEnum::ShowType show_pos_type ) {
	showPosType = show_pos_type;
	int parentMainWindowWidth;
	int parentMainWindowHeight;
	int currentWidth;
	parentMainWindowWidth = parentMainWindow->width( );
	parentMainWindowHeight = parentMainWindow->height( );
	currentWidth = parentMainWindowWidth / 3;
	switch( showPosType ) {
		case WidgetEnum::ShowType::Center :
			move( currentWidth, 0 );
			break;
		case WidgetEnum::ShowType::Left :
			move( 0, 0 );
			break;
		case WidgetEnum::ShowType::Right :
			move( currentWidth + currentWidth, 0 );
			break;
	}
	resize( currentWidth, parentMainWindowHeight );
	raise( );
}
bool NodeInfoWidget::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {

	bool eventFilter = QWidget::eventFilter( event_obj_ptr, event_type );
	if( isHidden( ) )
		return eventFilter;
	auto type = event_type->type( );
	switch( type ) {
		case QEvent::Resize :
			showNodeInfoWidget( showPosType );
			show( );
			break;
	}

	return eventFilter;
}
bool NodeInfoWidget::event( QEvent *event ) {
	bool eventResult = QWidget::event( event );
	auto type = event->type( );
	switch( type ) {
		case QEvent::Show :
			showNodeInfoWidget( showPosType );
			emit show_signal( this );
			break;
		case QEvent::Hide :
			node = nullptr;
			showPosType = WidgetEnum::ShowType::Center;
			emit hide_signal( this );
	}
	return eventResult;
}
