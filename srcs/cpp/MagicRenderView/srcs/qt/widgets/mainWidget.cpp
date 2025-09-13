#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "itemWidget.h"

#include "../tools/tools.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	appInstance = Application::getApplicationInstancePtr( );

	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );

	rightMouseBtnMenu = new QMenu( this );
	auto addAction = rightMouseBtnMenu->addAction( "天才" );
	connect( addAction, &QAction::triggered, this, &MainWidget::createNewItemWidget );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
	std_vector< ItemWidget * > buff( itemWidgets.begin( ), itemWidgets.end( ) );
	itemWidgets.clear( );
	size_t count = buff.size( );
	auto data = buff.data( );
	for( size_t index = 0; index < count; ++index )
		delete data[ index ];

}
void MainWidget::clickItemWidget( ItemWidget *click_item_widget ) {
	emit s_signals_clickItemWidget( click_item_widget );
	qDebug( ) << tools::debug::getFunctionName( );
}
void MainWidget::doubleClickItemWidget( ItemWidget *double_click_item_widget ) {
	emit s_signals_doubleClickItemWidget( double_click_item_widget );

	qDebug( ) << tools::debug::getFunctionName( );
}
void MainWidget::createNewItemWidget( bool flage ) {
	QObject *object = sender( );
	auto action = qobject_cast< QAction * >( object );
	if( action == nullptr )
		return;
	auto widget = new ItemWidget( this );
	widget->setFixedSize( 100, 100 );
	auto mapFromGlobal = this->mapFromGlobal( rightPos );
	widget->move( mapFromGlobal );
	widget->show( );
	QRect geometry = widget->geometry( );
	geometry.setHeight( geometry.height( ) + 10 );
	geometry.setWidth( geometry.width( ) + 10 );
	auto united = geometry.united( contentsRect( ) );
	auto newSize = united.size( );
	if( newSize != this->size( ) )
		setMinimumSize( newSize );
	// 存储窗口
	itemWidgets.emplace_back( widget );
	connect( widget, &ItemWidget::s_signals_deleteItemWidget, [this] ( ItemWidget *delete_obj_ptr ) {
		auto iterator = itemWidgets.begin( );
		auto end = itemWidgets.end( );
		for( ; iterator != end; ++iterator )
			if( *iterator == delete_obj_ptr ) {
				itemWidgets.erase( iterator );
				return;
			}
	} );
	connect( widget, &ItemWidget::s_signals_clickItemWidget, this, &MainWidget::clickItemWidget );
	connect( widget, &ItemWidget::s_signals_doubleClickItemWidget, this, &MainWidget::doubleClickItemWidget );

	emit s_signals_createNewItemWidget( widget, geometry, united );
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::darkGreen );
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	rightPos = QCursor::pos( );
	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnMenu->move( rightPos );
			rightMouseBtnMenu->show( );
			break;
	}
}
