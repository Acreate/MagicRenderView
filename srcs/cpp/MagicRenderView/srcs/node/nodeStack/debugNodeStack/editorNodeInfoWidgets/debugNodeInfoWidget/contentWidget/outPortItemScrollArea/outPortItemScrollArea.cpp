#include "outPortItemScrollArea.h"

#include "outPortItemScrollWidget.h"

OutPortItemScrollArea::OutPortItemScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	outPortItemScrollWidget = new OutPortItemScrollWidget( this );
	setWidget( outPortItemScrollWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
