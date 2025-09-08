#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include <qt/items/nodeRunFunctionSequenceItem.h>

#include "NodeRunSequenceItemWidget.h"

NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	rootItem = new NodeRunFunctionSequenceItem( this );
	rootItem->renderSubItemsNodeWidget->setFixedHeight( 400 );
}
void NodeRunSequenceWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodeRunSequenceWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	rootItem->renderSubItemsNodeWidget->setFixedWidth( this->width( ) );
}
void NodeRunSequenceWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
}
NodeRunFunctionSequenceItem * NodeRunSequenceWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {
	return rootItem->insertNodeRender( generater_scripts_widget, function_declaration, glob_point, set_point );
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {

	delete rootItem;
}
