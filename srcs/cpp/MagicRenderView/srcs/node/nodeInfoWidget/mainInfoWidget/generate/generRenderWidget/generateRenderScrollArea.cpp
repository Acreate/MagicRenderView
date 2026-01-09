#include "generateRenderScrollArea.h"

#include "generateRenderWidget.h"
GenerateRenderScrollArea::GenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new GenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
