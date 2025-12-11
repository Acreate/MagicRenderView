#include "nodeInfoWidget.h"

#include <QPainter>
#include <QMenuBar>
#include <qcoreevent.h>
#include <QScrollBar>

#include <win/mainWindow.h>

#include "../../../director/varDirector.h"

#include "../../../widget/mainWidgetScrollArea.h"

#include "../../node/node.h"
#include "../../nodeInfo/nodeRefLinkInfo.h"

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
	mainWidgetScrollArea = parentMainWindow->getMainWidgetScrollArea( );
	vScrollBar = mainWidgetScrollArea->verticalScrollBar( );
	hScrollBar = mainWidgetScrollArea->horizontalScrollBar( );

	mainWindowMenuBar = parentMainWindow->menuBar( );
	showPosType = WidgetEnum::ShowType::Center;
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
	if( editorNodeInfoScrollArea && varDirector->init( ) && editorNodeInfoScrollArea->initNode( check_node_ptr ) == false )
		return false;
	titile->setTitleText( check_node_ptr->toQString( ) );
	return true;
}
QString NodeInfoWidget::getTitleText( ) const {
	return titile->getTitleText( );
}
void NodeInfoWidget::showNodeInfoWidget( WidgetEnum::ShowType show_pos_type ) {

	showPosType = show_pos_type;
	QRect geometry;
	int parentMainWindowWidth;
	int parentMainWindowHeight;
	int currentWidth;
	geometry = mainWidgetScrollArea->geometry( );
	topOffsetY = geometry.y( );
	leftOffsetX = geometry.x( );
	offsetX = leftOffsetX + vScrollBar->width( );
	parentMainWindowWidth = parentMainWindow->width( ) - offsetX;
	offsetY = topOffsetY + hScrollBar->height( );
	parentMainWindowHeight = parentMainWindow->height( ) - offsetY;
	currentWidth = parentMainWindowWidth / 3;
	switch( showPosType ) {
		case WidgetEnum::ShowType::Center :
			move( currentWidth, topOffsetY );
			break;
		case WidgetEnum::ShowType::Left :
			move( 0, topOffsetY );
			break;
		case WidgetEnum::ShowType::Right :
			move( currentWidth + currentWidth, topOffsetY );
			break;
	}
	resize( currentWidth, parentMainWindowHeight );
	int titileWidth = titile->width( );
	titileWidth = ( currentWidth - titileWidth ) / 2;
	titile->move( titileWidth, 0 );
	int titileHeight = titile->height( );
	editorNodeInfoScrollArea->move( 0, titileHeight );
	int bottonToolHeight = buttonWidget->height( );
	bottonToolHeight = parentMainWindowHeight - bottonToolHeight;
	titileWidth = buttonWidget->width( );
	titileWidth = ( currentWidth - titileWidth ) / 2;
	buttonWidget->move( titileWidth, bottonToolHeight );
	titileHeight = bottonToolHeight - titileHeight;
	editorNodeInfoScrollArea->resize( currentWidth, titileHeight );
	raise( );
}
void NodeInfoWidget::removeCurrentRefNodeInfo( NodeRefLinkInfo *node_ref_link_info ) {
	if( node_ref_link_info->getCurrentNode( ) == node )
		hide( );
}
void NodeInfoWidget::okButtonEvent( ) {
	hide( );
}
void NodeInfoWidget::cancelButtonEvent( ) {
	hide( );
}
bool NodeInfoWidget::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {

	bool eventFilter = QWidget::eventFilter( event_obj_ptr, event_type );
	if( isHidden( ) )
		return eventFilter;
	auto type = event_type->type( );
	switch( type ) {
		case QEvent::Resize :
			showNodeInfoWidget( showPosType );
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
void NodeInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
