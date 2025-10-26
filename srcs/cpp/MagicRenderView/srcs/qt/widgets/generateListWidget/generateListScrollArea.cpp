#include "generateListScrollArea.h"

#include <qt/tools/tools.h>

#include "GenerateListWidget.h"
GenerateListScrollArea::GenerateListScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	tools::ui::moveDisplayCenter( this, 0 );
}
void GenerateListScrollArea::setInit( ) {
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
void GenerateListScrollArea::setGenerateListWidget( GenerateListWidget *generate_list_widget ) {
	generateListWidget = generate_list_widget;
	setWidget( generateListWidget );
}
