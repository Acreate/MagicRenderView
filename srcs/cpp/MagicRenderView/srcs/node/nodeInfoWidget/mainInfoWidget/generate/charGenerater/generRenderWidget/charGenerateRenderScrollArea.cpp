#include "charGenerateRenderScrollArea.h"

#include "charGenerateRenderWidget.h"

CharGenerateRenderScrollArea::CharGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new CharGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
