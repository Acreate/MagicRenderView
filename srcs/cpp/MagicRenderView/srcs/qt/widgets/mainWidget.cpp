#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "../node/generate/nodeItemGenerate.h"

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	scrollArea = scroll_area;
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( this );
	appInstance = Application::getApplicationInstancePtr( );

	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );

	rightMouseBtnMenu = new QMenu( this );
	auto infos = NodeItemGenerate::getNodeItemDirClassMetaInfos( );
	for( auto &item : infos ) {
		QString dirName = item.first;
		QMenu *dirMenu = rightMouseBtnMenu->addMenu( dirName );
		for( auto &className : item.second ) {
			auto addAction = dirMenu->addAction( className );
			connect( addAction, &QAction::triggered, [this, dirName, className]( ) {
				auto nodeItem = NodeItemGenerate::createNodeItem( this, dirName, className );
				if( nodeItem->intPortItems( ) == false ) {
					delete nodeItem;
					return;
				}
				nodeItem->move( fromGlobalReleasePoint );
				nodeItemList.emplace_back( nodeItem );
				update( );
			} );
		}
	}
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );

}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto iterator = nodeItemList.begin( );
	auto end = nodeItemList.end( );
	for( ; iterator != end; ++iterator ) {
		NodeItem *nodeItem = *iterator;
		painter.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
	}
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalReleasePos = QCursor::pos( );
	fromGlobalReleasePoint = mapFromGlobal( globalReleasePos );

	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnMenu->move( globalReleasePos );
			rightMouseBtnMenu->show( );
			break;
		case Qt::LeftButton :

			break;
	}

	update( );
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	mouseMovePoint = event->pos( );
	update( );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = mapFromGlobal( globalPressPos );
	switch( mouseButton ) {
		case Qt::LeftButton :

			break;
	}
}
