#include "generateListScrollArea.h"

#include <qt/tools/tools.h>

#include "GenerateListWidget.h"
GenerateListScrollArea::GenerateListScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	tools::ui::moveDisplayCenter( this, 0 );
	generateListWidget = new GenerateListWidget(this);
}
