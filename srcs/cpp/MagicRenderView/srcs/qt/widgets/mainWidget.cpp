#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "../items/nodeItem.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	appInstance = Application::getApplicationInstancePtr( );

	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );

	rightMouseBtnMenu = new QMenu( this );
	auto addAction = rightMouseBtnMenu->addAction( "天才" );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
	std_vector< decltype(itemWidgets)::value_type  > buff( itemWidgets.begin( ), itemWidgets.end( ) );
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

	rightPos = QCursor::pos( );
	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnMenu->move( rightPos );
			rightMouseBtnMenu->show( );
			break;
	}
}
