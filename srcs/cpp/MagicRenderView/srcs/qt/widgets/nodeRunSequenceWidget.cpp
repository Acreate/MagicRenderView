#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include <qt/items/nodeRunFunctionSequenceItem.h>

#include "NodeRunSequenceItemFunctionWidget.h"
#include "NodeRunSequenceItemWidget.h"

#include "../tools/tools.h"

NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	rootItem = new NodeRunFunctionSequenceItem( this );
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
void NodeRunSequenceWidget::itemSubWidgetShowEvent( NodeRunSequenceItemWidget *widget, bool is_show, NodeRunFunctionSequenceItem *item ) {
	// todo 改变函数显示窗口
	qDebug( ) << tools::debug::getFunctionName( ) << widget->isHidden( ) << ", " << is_show;
}
void NodeRunSequenceWidget::itemThisWidgetShowEvent( NodeRunSequenceItemFunctionWidget *widget, bool is_show, NodeRunFunctionSequenceItem *item ) {
	// todo 改变显示子序列显示窗口
	qDebug( ) << tools::debug::getFunctionName( ) << widget->isHidden( ) << ", " << is_show;
}
void NodeRunSequenceWidget::itemThisWidgetCurrentItemDoubleClick( NodeRunSequenceItemFunctionWidget *widget, NodeRunFunctionSequenceItem *item ) {
	// todo 改变项显示子项目的能力
	qDebug( ) << tools::debug::getFunctionName( ) << widget->isHidden( );
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {

	delete rootItem;
}
