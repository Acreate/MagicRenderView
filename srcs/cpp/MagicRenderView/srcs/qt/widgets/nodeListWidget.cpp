#include "./nodeListWidget.h"

#include <QPainter>
#include <QTreeWidget.h>
#include <qboxlayout.h>
#include <qevent.h>
#include <qfileinfo.h>

#include <qt/application/application.h>

#include "nodeGeneraterListWidget.h"
#include "nodeTypeTreeListWidget.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;
	keyFirst = "Application/MainWindow/MainWidget/NodeListWidget";

	appInstance = Application::getApplicationInstancePtr( );

	nodeGeneraterListWidget = new NodeGeneraterListWidget( this );
	nodeTypeTreeListWidget = new NodeTypeTreeListWidget( nodeGeneraterListWidget, this );
	appInstance->syncAppValueIniFile( );

	quint64 nodeTypeListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeTreeListWidget, "width" ), 30 ).toULongLong( );
	nodeTypeTreeListWidget->setFixedWidth( nodeTypeListWidth );

	quint64 nodeGeneraterListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "width" ), 80 ).toULongLong( );
	nodeGeneraterListWidget->setFixedWidth( nodeGeneraterListWidth );

	QString showWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "showWidget" ), "" ).toString( );
}
NodeListWidget::~NodeListWidget( ) {
	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodeListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateWidgetListLayout( event->oldSize( ), event->size( ) );
}
void NodeListWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	mouseIsPress = true;
}
void NodeListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	mouseIsPress = false;
}

QWidget * NodeListWidget::mouseToPoint( const QPoint &point ) {
	int y = point.y( );
	int x = point.x( );
	if( x < 0 || y < 0 || height( ) < y || width( ) < x )
		return dragWidgetSize;
	if( mouseIsPress == false ) {
		auto nodeGeneraterListX = nodeGeneraterListWidget->pos( ).x( );
		if( abs( x - nodeGeneraterListX ) < 5 )
			dragWidgetSize = nodeGeneraterListWidget;
		else
			dragWidgetSize = nullptr;
	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeGeneraterListWidget ) {
			nodeGeneraterListWidget->move( x, 0 ); // 移动到新位置
			nodeTypeTreeListWidget->setFixedWidth( x );
			auto newWidth = width( ) - x;
			nodeGeneraterListWidget->setFixedWidth( newWidth );
		}
	}
	return dragWidgetSize;
}
void NodeListWidget::updateWidgetListLayout( const QSize &old_size, const QSize &current_size ) {

	int newWidth = current_size.width( );

	int nodeTypeListWidth = nodeTypeTreeListWidget->width( );
	int nodeGeneraterListWidth = nodeGeneraterListWidget->width( );

	int width = nodeGeneraterListWidth + nodeTypeListWidth;

	nodeTypeListWidth = nodeTypeListWidth * newWidth / width;

	width = newWidth - nodeTypeListWidth;
	auto height = current_size.height( );
	nodeTypeTreeListWidget->setFixedSize( nodeTypeListWidth, height );
	nodeGeneraterListWidget->setFixedSize( width, height );

	nodeTypeTreeListWidget->move( 0, 0 );
	width = nodeTypeTreeListWidget->width( );
	nodeGeneraterListWidget->move( width, 0 );
}
void NodeListWidget::writeHeightIni( ) const {
	int nodeTypeListWidth = nodeTypeTreeListWidget->width( );
	int nodeGeneraterListWidth = nodeGeneraterListWidget->width( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeTreeListWidget, "width" ), nodeTypeListWidth );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "width" ), nodeGeneraterListWidth );
}
