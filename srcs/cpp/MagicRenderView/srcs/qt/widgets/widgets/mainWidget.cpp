#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <qboxlayout.h>

#include "../../application/application.h"

#include "../scrollAreas/nodeListScrollAreasWidget.h"
#include "../scrollAreas/nodeRenderScrollAreasWidget.h"
#include "../scrollAreas/nodeScriptsScrollAreasWidget.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {

	appInstance = Application::getApplicationInstancePtr( );

	nodeListWidget = new NodeListScrollAreasWidget( this );
	nodeRenderWidget = new NodeRenderScrollAreasWidget( this );
	nodeScriptsWidget = new NodeScriptsScrollAreasWidget( this );

	keyFirst = "Application/MainWindow/MainWidget";

	if( appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "show" ), true ).toBool( ) )
		nodeScriptsWidget->show( );
	if( appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "show" ), true ).toBool( ) )
		nodeRenderWidget->show( );
	if( appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "show" ), true ).toBool( ) )
		nodeListWidget->show( );

	appInstance->syncAppValueIniFile( );

	quint64 nodeScriptsHeight = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "height" ), 50 ).toULongLong( );
	nodeScriptsWidget->setFixedHeight( nodeScriptsHeight );
	quint64 nodeListHeight = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "height" ), 50 ).toULongLong( );
	nodeListWidget->setFixedHeight( nodeListHeight );

	quint64 nodeRenderWidgetHeight = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "height" ), 100 ).toULongLong( );
	nodeRenderWidget->setFixedHeight( nodeRenderWidgetHeight );

	dragWidgetSize = nullptr;
	mouseIsPress = false;
	appInstance->setNodeListWidget( nodeListWidget->getNodeListWidget( ) );
}
MainWidget::~MainWidget( ) {
	writeShowIni( );
	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void MainWidget::mouseToPoint( const QPoint &point ) {
	int y = point.y( );
	int x = point.x( );
	if( x < 0 || y < 0 || height( ) < y || width( ) < x )
		return;
	if( mouseIsPress == false ) {
		auto nodeListWidgetPosY = nodeListWidget->pos( ).y( );
		if( abs( y - nodeListWidgetPosY ) < 5 )
			dragWidgetSize = nodeListWidget;
		else {
			nodeListWidgetPosY = nodeScriptsWidget->pos( ).y( );
			if( abs( y - nodeListWidgetPosY ) < 5 )
				dragWidgetSize = nodeScriptsWidget;
			else
				dragWidgetSize = nullptr;
		}
		if( dragWidgetSize && cursor( ) != Qt::SizeVerCursor )
			setCursor( Qt::SizeVerCursor ); // 设置鼠标样式
		else if( dragWidgetSize == nullptr && cursor( ) != Qt::ArrowCursor )
			setCursor( Qt::ArrowCursor ); // 设置鼠标样式
	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeListWidget ) {
			nodeListWidget->move( 0, y ); // 移动到新位置
			nodeRenderWidget->setFixedHeight( y );
			auto newHeight = height( ) - y - nodeScriptsWidget->height( );
			nodeListWidget->setFixedHeight( newHeight );
		} else if( dragWidgetSize == nodeScriptsWidget ) {

			nodeScriptsWidget->move( 0, y ); // 移动到新位置
			auto newHeight = y - nodeRenderWidget->height( );
			nodeListWidget->setFixedHeight( newHeight );
			newHeight = height( ) - y;
			nodeScriptsWidget->setFixedHeight( newHeight );
		}
	}
}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateWidgetListLayout( event->oldSize( ), event->size( ) );
}
void MainWidget::updateWidgetListLayout( const QSize &old_size, const QSize &current_size ) {

	int newHeight = current_size.height( );

	int nodeScriptsWidgetHeight = nodeScriptsWidget->height( );
	int nodeRenderWidgetHeight = nodeRenderWidget->height( );
	int nodeListWidgetHeight = nodeListWidget->height( );
	int height = nodeRenderWidgetHeight + nodeScriptsWidgetHeight + nodeListWidgetHeight;

	nodeScriptsWidgetHeight = nodeScriptsWidgetHeight * newHeight / height;
	nodeListWidgetHeight = nodeListWidgetHeight * newHeight / height;

	height = newHeight - nodeScriptsWidgetHeight - nodeListWidgetHeight;
	auto width = current_size.width( );
	nodeScriptsWidget->setFixedSize( width, nodeScriptsWidgetHeight );
	nodeListWidget->setFixedSize( width, nodeListWidgetHeight );
	nodeRenderWidget->setFixedSize( width, height );

	nodeRenderWidget->move( 0, 0 );
	height = nodeRenderWidget->height( );
	nodeListWidget->move( 0, height );
	height = height + nodeListWidget->height( );
	nodeScriptsWidget->move( 0, height );

	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void MainWidget::writeHeightIni( ) const {

	int nodeScriptsWidgetHeight = nodeScriptsWidget->height( );
	int nodeRenderWidgetHeight = nodeRenderWidget->height( );
	int nodeListWidgetHeight = nodeListWidget->height( );

	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "height" ), nodeScriptsWidgetHeight );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "height" ), nodeRenderWidgetHeight );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "height" ), nodeListWidgetHeight );

}
void MainWidget::writeShowIni( ) const {
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "show" ), nodeScriptsWidget->isHidden( ) == false );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "show" ), nodeRenderWidget->isHidden( ) == false );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "show" ), nodeListWidget->isHidden( ) == false );
}

void MainWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::darkGreen );
}

void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	mouseIsPress = true;
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;
	if( cursor( ) != Qt::ArrowCursor ) {
		setCursor( Qt::ArrowCursor ); // 设置鼠标样式
		writeHeightIni( );
		appInstance->syncAppValueIniFile( );
	}
}
bool MainWidget::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::MouseMove :
			break;
	}
	return QWidget::event( event );
}
