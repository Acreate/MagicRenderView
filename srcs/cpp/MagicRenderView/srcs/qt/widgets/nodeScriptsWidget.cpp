#include "./nodeScriptsWidget.h"

#include <QPainter>
#include <qevent.h>

#include <qt/application/application.h>

#include "nodeDefineVarWidget.h"
#include "nodeRunSequenceAreasWidget.h"

NodeScriptsWidget::NodeScriptsWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {

	mouseIsPress = false;
	dragWidgetSize = nullptr;
	keyFirst = "Application/MainWindow/MainWidget/NodeScriptsWidget";

	applicationInstancePtr = Application::getApplicationInstancePtr( );
	connect( applicationInstancePtr, &Application::dragEventEnd, this, &NodeScriptsWidget::dragEventEnd );
	mouseIsPress = false;

	nodeDefineVarWidget = new NodeDefineVarWidget( this );
	nodeRunSequenceAreasWidget = new NodeRunSequenceAreasWidget( this );

	applicationInstancePtr->syncAppValueIniFile( );

	quint64 nodeDefineVarWidth = applicationInstancePtr->getAppIniValue( applicationInstancePtr->normalKeyAppendEnd( keyFirst, nodeDefineVarWidget, "width" ), 30 ).toULongLong( );

	quint64 nodeRunSequenceWidth = applicationInstancePtr->getAppIniValue( applicationInstancePtr->normalKeyAppendEnd( keyFirst, nodeRunSequenceAreasWidget, "width" ), 80 ).toULongLong( );

	nodeRunSequenceAreasWidget->setFixedWidth( nodeRunSequenceWidth );
	nodeDefineVarWidget->setFixedWidth( nodeDefineVarWidth );

	applicationInstancePtr->setNodeScriptsWidget( this );
}
NodeScriptsWidget::~NodeScriptsWidget( ) {
	writeHeightIni( );
	applicationInstancePtr->syncAppValueIniFile( );
}
void NodeScriptsWidget::writeHeightIni( ) const {
	int nodeRunSequenceWidth = nodeRunSequenceAreasWidget->width( );
	int nodeDefineVarWidth = nodeDefineVarWidget->width( );
	applicationInstancePtr->setAppIniValue( applicationInstancePtr->normalKeyAppendEnd( keyFirst, nodeRunSequenceAreasWidget, "width" ), nodeRunSequenceWidth );
	applicationInstancePtr->setAppIniValue( applicationInstancePtr->normalKeyAppendEnd( keyFirst, nodeDefineVarWidget, "width" ), nodeDefineVarWidth );
}
QWidget * NodeScriptsWidget::mouseToPoint( const QPoint &point ) {
	int y = point.y( );
	int x = point.x( );
	if( x < 0 || y < 0 || height( ) < y || width( ) < x )
		return dragWidgetSize;
	if( mouseIsPress == false ) { // nodeRunSequenceAreasWidget -> nodeDefineVarWidget
		auto nodeGeneraterListX = nodeRunSequenceAreasWidget->pos( ).x( );
		if( abs( x - nodeGeneraterListX ) < 5 )
			dragWidgetSize = nodeRunSequenceAreasWidget;
		else
			dragWidgetSize = nullptr;
	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeRunSequenceAreasWidget ) {
			nodeRunSequenceAreasWidget->move( x, 0 ); // 移动到新位置
			nodeDefineVarWidget->setFixedWidth( x );
			auto newWidth = width( ) - x;
			nodeRunSequenceAreasWidget->setFixedWidth( newWidth );
		}
	}
	return dragWidgetSize;
}

void NodeScriptsWidget::updateWidgetListLayout( const QSize &old_size, const QSize &current_size ) {

	int newWidth = current_size.width( );

	int nodeRunSequenceWidth = nodeRunSequenceAreasWidget->width( );
	int nodeDefineVarWidth = nodeDefineVarWidget->width( );

	int width = nodeDefineVarWidth + nodeRunSequenceWidth;

	nodeRunSequenceWidth = nodeRunSequenceWidth * newWidth / width;

	width = newWidth - nodeRunSequenceWidth;
	auto height = current_size.height( );
	nodeDefineVarWidget->setFixedSize( width, height );
	nodeRunSequenceAreasWidget->setFixedSize( nodeRunSequenceWidth, height );
	nodeDefineVarWidget->move( 0, 0 );
	width = nodeDefineVarWidget->width( );
	nodeRunSequenceAreasWidget->move( width, 0 );
}

void NodeScriptsWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodeScriptsWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	mouseIsPress = true;
}
void NodeScriptsWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	mouseIsPress = false;
}
void NodeScriptsWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateWidgetListLayout( event->oldSize( ), event->size( ) );
}
void NodeScriptsWidget::dragEventEnd( Application *event_obj, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glbal_point ) {
	auto fromGlobal = nodeRunSequenceAreasWidget->mapFromGlobal( glbal_point );
	if( nodeRunSequenceAreasWidget->contentsRect( ).contains( fromGlobal ) == false )
		return;
	nodeRunSequenceAreasWidget->setRunFunctionWidget( this, function_declaration, glbal_point, fromGlobal );
}
