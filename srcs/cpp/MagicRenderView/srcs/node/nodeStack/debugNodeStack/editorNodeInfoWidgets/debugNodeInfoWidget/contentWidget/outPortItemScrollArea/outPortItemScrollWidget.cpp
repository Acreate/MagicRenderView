#include "outPortItemScrollWidget.h"

#include <QPainter>
#include <QVBoxLayout>

#include "outPortItemWidget.h"
OutPortItemScrollWidget::OutPortItemScrollWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
}
OutPortItemScrollWidget::~OutPortItemScrollWidget( ) {
	clear( );
}
bool OutPortItemScrollWidget::appendOutputItem( OutputPort *output_port_ptr, const QString &msg ) {
	auto item = new OutPortItemWidget( this );
	item->setInfo( output_port_ptr, msg );
	mainLayout->addWidget( item );
	outputPortItemList.emplace_back( item );
	return true;
}
bool OutPortItemScrollWidget::clear( ) {
	for( auto *item : outputPortItemList )
		delete item;
	outputPortItemList.clear( );
	return true;
}
void OutPortItemScrollWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
