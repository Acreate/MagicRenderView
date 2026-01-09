#include "nodeInfoWidget.h"

#include <QPainter>
#include <QMenuBar>
#include <qcoreevent.h>
#include <QScrollBar>

#include "../../../director/varDirector.h"
#include "../../../widget/mainWidgetScrollArea.h"
#include "../../node/node.h"
#include "../bottomTool/bottomNodeInfoTool.h"
#include "../editNodeInfoScrollArea/editorNodeInfoScrollArea.h"
#include "../title/nodeInfoTitle.h"

NodeInfoWidget::NodeInfoWidget( ) : editorNodeInfoScrollArea( nullptr ) {
	setMinimumSize( 100, 250 );
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

	showPosType = WidgetEnum::ShowType::Center;
}
NodeInfoWidget::~NodeInfoWidget( ) {
	emit release_signal( this );
	if( editorNodeInfoScrollArea )
		delete editorNodeInfoScrollArea;
	delete varDirector;
}
void NodeInfoWidget::updatePos( ) {
	if( mainWidgetScrollArea == nullptr )
		return;
	auto point = mainWidgetScrollArea->pos( );
	point = mainWidgetScrollArea->mapToGlobal( point );
	move( point );
}
void NodeInfoWidget::updateLayout( ) {

}
void NodeInfoWidget::setMainWidgetScrollArea( MainWidgetScrollArea *main_widget_scroll_area ) {
	mainWidgetScrollArea = main_widget_scroll_area;
	updatePos( );
}
bool NodeInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr == nullptr || editorNodeInfoScrollArea == nullptr || varDirector->init( ) == false )
		return false;
	if( editorNodeInfoScrollArea->initNode( check_node_ptr ) == false )
		return false;
	titile->setTitleText( check_node_ptr->toQString( ) );
	return true;
}
Node * NodeInfoWidget::getNode( ) const { return editorNodeInfoScrollArea->getCurrentNode( ); }
QString NodeInfoWidget::getTitleText( ) const {
	return titile->getTitleText( );
}
void NodeInfoWidget::okButtonEvent( ) {
	hide( );
}
void NodeInfoWidget::cancelButtonEvent( ) {
	hide( );
}
bool NodeInfoWidget::event( QEvent *event ) {
	bool eventResult = QWidget::event( event );
	auto type = event->type( );
	switch( type ) {
		case QEvent::Resize :
			updateLayout( );
			break;
		case QEvent::Show :
			updatePos( );
			updateLayout( );
			emit show_signal( this );
			break;
		case QEvent::Hide :
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
