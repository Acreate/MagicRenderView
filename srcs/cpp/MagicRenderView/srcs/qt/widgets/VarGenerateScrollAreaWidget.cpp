#include "VarGenerateScrollAreaWidget.h"

#include "varGenerateWidget.h"
VarGenerateScrollAreaWidget::VarGenerateScrollAreaWidget( QWidget *parent ) : QScrollArea( parent ) {
	contentWidget = new VarGenerateWidget( this );
	setWidget( contentWidget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
