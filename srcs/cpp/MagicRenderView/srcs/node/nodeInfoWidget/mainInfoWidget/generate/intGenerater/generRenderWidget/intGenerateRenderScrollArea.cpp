#include "intGenerateRenderScrollArea.h"

#include "intGenerateRenderWidget.h"

IntGenerateRenderScrollArea::IntGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new IntGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
