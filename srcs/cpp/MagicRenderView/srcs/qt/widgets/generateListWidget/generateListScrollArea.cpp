#include "generateListScrollArea.h"

#include <qt/tools/tools.h>

#include "GenerateListWidget.h"
GenerateListScrollArea::GenerateListScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	tools::ui::moveDisplayCenter( this, 0 );
	generateListWidget = new GenerateListWidget( this );
	setWidget( generateListWidget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setMinimumSize( 200, 300 );
	setBaseSize( 200, 300 );
}
