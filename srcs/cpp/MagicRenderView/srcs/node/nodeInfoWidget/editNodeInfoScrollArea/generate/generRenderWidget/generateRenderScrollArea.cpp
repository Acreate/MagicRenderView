#include "generateRenderScrollArea.h"

#include "generateRenderWidget.h"
GenerateRenderScrollArea::GenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new GenerateRenderWidget( this );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
