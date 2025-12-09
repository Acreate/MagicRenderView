#include "generatePanelWidget.h"
GeneratePanelWidget::GeneratePanelWidget( const std::function<void *(const QString &type_name, const QString &var_name)> &create_type_var, QWidget *parent ): QScrollArea( parent ),
	createTypeVar( create_type_var ) { }
bool GeneratePanelWidget::appendItem( const QString &type_name, const QString &var_name ) {
	return false;
}
void GeneratePanelWidget::resizeEvent( QResizeEvent *resize_event ) {
	QScrollArea::resizeEvent( resize_event );
}
