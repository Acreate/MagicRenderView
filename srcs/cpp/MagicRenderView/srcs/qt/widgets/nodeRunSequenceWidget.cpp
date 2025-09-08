#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include <qt/items/nodeRunFunctionSequenceItem.h>


NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	rootItem = new NodeRunFunctionSequenceItem( this );
	itemWidth = 100;
	itemHeight = 250;
	itemSpaceWidth = 2;
	itemSpaceHeight = 5;
}
void NodeRunSequenceWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodeRunSequenceWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
void NodeRunSequenceWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );

}
NodeRunFunctionSequenceItem * NodeRunSequenceWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {

	return nullptr;
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {

	delete rootItem;
}
