#include "outPortItemScorllWidget.h"

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
