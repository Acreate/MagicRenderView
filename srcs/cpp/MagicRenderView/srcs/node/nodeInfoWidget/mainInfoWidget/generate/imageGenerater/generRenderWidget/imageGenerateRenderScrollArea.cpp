#include "imageGenerateRenderScrollArea.h"

#include "imageGenerateRenderWidget.h"

ImageGenerateRenderScrollArea::ImageGenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new ImageGenerateRenderWidget( this );
	setWidget( viewWidget );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
