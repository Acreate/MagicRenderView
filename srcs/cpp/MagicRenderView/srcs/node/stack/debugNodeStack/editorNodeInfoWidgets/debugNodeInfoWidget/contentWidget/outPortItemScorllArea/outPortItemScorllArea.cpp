#include "outPortItemScorllArea.h"

#include "outPortItemScorllWidget.h"
OutPortItemScorllArea::OutPortItemScorllArea( QWidget *parent ) {
	outPortItemScorllWidget = new OutPortItemScorllWidget( this );
	setWidget( outPortItemScorllWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
