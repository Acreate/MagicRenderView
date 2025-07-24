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

	dragWidgetSize = nullptr;
	mouseIsPress = false;
	nodeScriptsWidget->setMouseTracking( true );
	nodeRenderWidget->setMouseTracking( true );
	nodeListWidget->setMouseTracking( true );

	nodeListWidget->widget( )->setMouseTracking( true );
	nodeRenderWidget->widget( )->setMouseTracking( true );
	nodeScriptsWidget->widget( )->setMouseTracking( true );
}
MainWidget::~MainWidget( ) {

	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "show" ), nodeScriptsWidget->isHidden( ) == false );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "show" ), nodeRenderWidget->isHidden( ) == false );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "show" ), nodeListWidget->isHidden( ) == false );

	int nodeScriptsWidgetHeight = nodeScriptsWidget->height( );
	int nodeRenderWidgetHeight = nodeRenderWidget->height( );
	int nodeListWidgetHeight = nodeListWidget->height( );

	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "height" ), nodeScriptsWidgetHeight );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeRenderWidget, "height" ), nodeRenderWidgetHeight );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "height" ), nodeListWidgetHeight );

	appInstance->syncAppValueIniFile( );
}
void MainWidget::initWidgetListLayout( ) {

	auto size = this->contentsRect( ).size( );
	double height = size.height( );
	double mulBase = height / ( 8 + 3 + 3 );
	auto width = mulBase * 3;

	quint64 nodeScriptsHeight = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeScriptsWidget, "height" ), width ).toULongLong( );

	quint64 nodeListHeight = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeListWidget, "height" ), width ).toULongLong( );

	height = height - nodeScriptsHeight - nodeListHeight;
	width = size.width( );
	nodeScriptsWidget->setFixedSize( width, nodeScriptsHeight );
	nodeListWidget->setFixedSize( width, nodeListHeight );
	nodeRenderWidget->setFixedSize( width, height );

	nodeRenderWidget->move( 0, 0 );
	nodeListWidget->move( 0, height );
	width = height + nodeListWidget->height( );
	nodeScriptsWidget->move( 0, width );
}

void MainWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::darkGreen );
}

void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	// 检测子窗口拉伸功能
	auto point = event->pos( );

	int y = point.y( );
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
		if( dragWidgetSize && cursorShape != Qt::SizeVerCursor ) {
			setCursor( Qt::SizeVerCursor ); // 设置鼠标样式
			cursorShape = Qt::SizeVerCursor;
		} else if( dragWidgetSize == nullptr && cursorShape != Qt::ArrowCursor ) {
			setCursor( Qt::ArrowCursor ); // 设置鼠标样式
			cursorShape = Qt::ArrowCursor;
		}
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
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	mouseIsPress = true;
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;
	if( cursorShape != Qt::ArrowCursor ) {
		setCursor( Qt::ArrowCursor ); // 设置鼠标样式
		cursorShape = Qt::ArrowCursor;
	}
}
