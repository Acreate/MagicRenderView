#include "uIntGenerateRenderScrollArea.h"

#include "uIntGenerateRenderWidget.h"

UIntGenerateRenderScrollArea::UIntGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new UIntGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
