#include "binGenerateRenderScrollArea.h"

#include "binGenerateRenderWidget.h"

BinGenerateRenderScrollArea::BinGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new BinGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
