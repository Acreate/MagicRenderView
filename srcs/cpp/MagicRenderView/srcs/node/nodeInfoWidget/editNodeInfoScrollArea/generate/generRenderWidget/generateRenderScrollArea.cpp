#include "generateRenderScrollArea.h"

#include "../generateItemWidget/generateItemWidget.h"
GenerateRenderScrollArea::GenerateRenderScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	viewWidget = new GenerateItemWidget( this );
	setWidgetResizable( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
