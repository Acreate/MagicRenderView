#include "floatGenerateRenderScrollArea.h"

#include "floatGenerateRenderWidget.h"

FloatGenerateRenderScrollArea::FloatGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new FloatGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
