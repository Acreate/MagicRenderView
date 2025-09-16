#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "../node/generate/nodeItemGenerate.h"
#include "../node/prot/inputProt/nodeInputPort.h"

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
				activeItem = nodeItem;
				update( );
			} );
		}
	}
	selectInputPort = nullptr;
	selectOutputPort = nullptr;
	activeItem = nullptr;
	selectItem = nullptr;
	dragItem = nullptr;
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
	// 不在拖拽情况下，绘制动态线
	if( dragItem == nullptr && selectItem )
		painter.drawLine( modPoint, mouseMovePoint );
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
	if( selectInputPort && selectOutputPort )
		selectInputPort->linkOutputPort( selectOutputPort );
	selectInputPort = nullptr;
	selectOutputPort = nullptr;
	activeItem = nullptr;
	selectItem = nullptr;
	dragItem = nullptr;
	update( );
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( selectItem == nullptr )
		return;
	mouseMovePoint = event->pos( );
	if( dragItem )
		dragItem->move( mouseMovePoint - modPoint );
	update( );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = mapFromGlobal( globalPressPos );
	switch( mouseButton ) {
		case Qt::LeftButton :
			for( NodeItem *item : nodeItemList ) {
				QPoint itemPos = item->getPos( );
				modPoint = fromGlobalPressPoint - itemPos;
				NodeItem::Click_Type pointType = item->relativePointType( modPoint );
				if( pointType == NodeItem::Click_Type::None )
					continue;
				if( pointType == NodeItem::Click_Type::OutputPort ) {
					selectOutputPort = item->getNodeOutputPortAtRelativePointType( modPoint );
					if( selectOutputPort )
						item->getOutputPortPos( selectOutputPort, modPoint );
					else
						dragItem = item;
				} else if( pointType == NodeItem::Click_Type::InputPort ) {
					selectInputPort = item->getNodeInputAtRelativePointType( modPoint );
					if( selectInputPort )
						item->getInputPortPos( selectInputPort, modPoint );
					else
						dragItem = item;
				} else
					dragItem = item;
				activeItem = selectItem = item;
				break;
			}
			break;
	}
}
