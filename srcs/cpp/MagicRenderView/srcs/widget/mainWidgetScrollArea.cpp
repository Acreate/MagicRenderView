#include "mainWidgetScrollArea.h"

#include "mainWidget.h"

MainWidgetScrollArea::MainWidgetScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	mainWidget = new MainWidget( this );

	setWidget( mainWidget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
