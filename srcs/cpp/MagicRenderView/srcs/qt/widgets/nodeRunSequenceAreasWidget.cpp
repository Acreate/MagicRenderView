#include "./nodeRunSequenceAreasWidget.h"

#include "nodeRunFunctionSequenceItemWidget.h"
#include "nodeRunSequenceWidget.h"

NodeRunSequenceAreasWidget::NodeRunSequenceAreasWidget( QWidget *parent ) : QScrollArea( parent ) {
	mainWidget = new NodeRunSequenceWidget( this );
	setWidget( mainWidget );
	this->setWidgetResizable( true );
}
NodeRunFunctionSequenceItemWidget * NodeRunSequenceAreasWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {
	return mainWidget->setRunFunctionWidget( generater_scripts_widget, function_declaration, glob_point, set_point );
}
