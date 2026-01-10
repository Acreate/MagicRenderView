#include "colorGenerateRenderScrollArea.h"

#include "colorGenerateRenderWidget.h"

ColorGenerateRenderScrollArea::ColorGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new ColorGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
