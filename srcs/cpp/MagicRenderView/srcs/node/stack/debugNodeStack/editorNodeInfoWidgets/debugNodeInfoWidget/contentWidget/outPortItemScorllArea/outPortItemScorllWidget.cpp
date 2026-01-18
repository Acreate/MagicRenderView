#include "outPortItemScorllWidget.h"

#include <QPainter>
#include <QVBoxLayout>

#include "outPortItemWidget.h"
OutPortItemScorllWidget::OutPortItemScorllWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
}
OutPortItemScorllWidget::~OutPortItemScorllWidget( ) {
	for( auto *item : outputPortItemList )
		delete item;
	outputPortItemList.clear( );
}
bool OutPortItemScorllWidget::appendOutputItem( OutputPort *output_port_ptr, const QString &msg ) {
	auto item = new OutPortItemWidget( this );
	item->setInfo( output_port_ptr, msg );
	mainLayout->addWidget( item );
	outputPortItemList.emplace_back( item );
	return true;
}
bool OutPortItemScorllWidget::clear( ) {
	for( auto *item : outputPortItemList )
		delete item;
	outputPortItemList.clear( );
	return true;
}
void OutPortItemScorllWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	//QPainter painter( this );
	//painter.fillRect( contentsRect( ), Qt::GlobalColor::blue );
}
