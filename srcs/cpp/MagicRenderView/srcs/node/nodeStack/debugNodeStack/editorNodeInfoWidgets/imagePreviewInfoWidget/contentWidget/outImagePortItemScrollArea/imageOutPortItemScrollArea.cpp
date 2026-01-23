#include "imageOutPortItemScrollArea.h"

#include "imageOutPortItemScrollWidget.h"

ImageOutPortItemScrollArea::ImageOutPortItemScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	this->imageOutPortItemScrollWidget = new ImageOutPortItemScrollWidget( this );
	setWidget( imageOutPortItemScrollWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
