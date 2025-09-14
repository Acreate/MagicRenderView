#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "../items/nodeItemWidget.h"

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

	auto generateItems = NodeItemWidget::getGenerateItems( );
	auto topPairPtr = generateItems.data( );
	size_t count = generateItems.size( );
	size_t index = 0;
	QString *subPtr;
	size_t subCount;
	size_t subIndex;
	QAction *action;
	for( ; index < count; ++index ) {
		auto subMenu = new QMenu( this );
		auto &pair = topPairPtr[ index ];
		auto &dirName = pair.first;
		subMenu->setTitle( dirName );
		rightMouseBtnMenu->addMenu( subMenu );
		subCount = pair.second.size( );
		subPtr = pair.second.data( );
		subIndex = 0;
		for( ; subIndex < subCount; ++subIndex ) {
			auto &nodeName = subPtr[ subIndex ];
			action = subMenu->addAction( nodeName );
			connect( action, &QAction::triggered, [this, dirName, nodeName]( ) {
				auto itemWidget = NodeItemWidget::generateNode( this, dirName, nodeName );
				itemWidget->move( fromGlobalReleasePoint );
				itemWidget->show( );
				QRect geometry = itemWidget->geometry( );
				auto size = geometry.united( contentsRect( ) ).size( );
				if( this->size( ) != size )
					this->setMinimumSize( size );
				QPoint point = geometry.bottomRight( );
				scrollArea->ensureVisible( point.x( ), point.y( ) );
				activeNodeItemWidget = itemWidget;
				itemWidgets.emplace_back( itemWidget );
			} );
		}
	}
	selectNodeItemWidget = nullptr;
	selectProtOutputItemWidget = nullptr;
	selectProtInputItemWidget = nullptr;
	activeNodeItemWidget = nullptr;
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
	std_vector< decltype(itemWidgets)::value_type > buff( itemWidgets.begin( ), itemWidgets.end( ) );
	itemWidgets.clear( );
	size_t count = buff.size( );
	auto data = buff.data( );
	for( size_t index = 0; index < count; ++index )
		delete data[ index ];
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::darkGreen );
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalReleasePos = QCursor::pos( );
	fromGlobalReleasePoint = mapFromGlobal( globalReleasePos );
	ProtInputItemWidget *protInputItemWidget = nullptr;
	ProtOutputItemWidget *protOutputItemWidget = nullptr;
	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnMenu->move( globalReleasePos );
			rightMouseBtnMenu->show( );
			break;
		case Qt::LeftButton :
			// 没有找到按下时的接口
			if( selectNodeItemWidget == nullptr )
				break;
			for( auto &nodeItemWidge : itemWidgets )
				if( nodeItemWidge->geometry( ).contains( fromGlobalReleasePoint ) ) {
					activeNodeItemWidget = nodeItemWidge;
					if( selectProtInputItemWidget ) {
						protOutputItemWidget = nodeItemWidge->getProtOutputItemWidget( globalReleasePos );
					} else {
						protInputItemWidget = nodeItemWidge->getProtInputItemWidget( globalReleasePos );
					}
					break;
				}
			break;
	}

	selectNodeItemWidget = nullptr;
	selectProtOutputItemWidget = nullptr;
	selectProtInputItemWidget = nullptr;
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( selectNodeItemWidget == nullptr )
		return;

}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = mapFromGlobal( globalPressPos );
	switch( mouseButton ) {
		case Qt::LeftButton :
			for( auto &nodeItemWidge : itemWidgets )
				if( nodeItemWidge->geometry( ).contains( fromGlobalPressPoint ) ) {
					selectNodeItemWidget = nodeItemWidge;
					selectProtOutputItemWidget = nodeItemWidge->getProtOutputItemWidget( globalPressPos );
					if( selectProtOutputItemWidget == nullptr )
						selectProtInputItemWidget = nodeItemWidge->getProtInputItemWidget( globalPressPos );
					break;
				}

			break;
	}
}
