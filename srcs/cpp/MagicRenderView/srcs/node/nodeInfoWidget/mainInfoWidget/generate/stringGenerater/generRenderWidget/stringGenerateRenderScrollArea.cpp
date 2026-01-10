#include "stringGenerateRenderScrollArea.h"

#include "stringGenerateRenderWidget.h"

StringGenerateRenderScrollArea::StringGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new StringGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
