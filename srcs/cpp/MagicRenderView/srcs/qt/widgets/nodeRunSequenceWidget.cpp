#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include <qt/items/nodeRunFunctionSequenceItem.h>

#include "NodeRunSequenceItemFunctionWidget.h"
#include "NodeRunSequenceItemWidget.h"

#include "../tools/tools.h"

NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	space = 5;
	top = 5;
	rootItem = new NodeRunFunctionSequenceItem( this );
	rootItem->renderSubItemsNodeWidget->setFixedSize( 100, 200 );
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
void NodeRunSequenceWidget::itemChange( NodeRunFunctionSequenceItem *item ) {

	NodeRunSequenceItemWidget *itemWidget = item->renderSubItemsNodeWidget;
	if( itemWidget->isHidden( ) ) // 如果窗口不显示，那么我们ui显示
		return;
	auto &subItems = item->subItems;
	auto iterator = subItems.begin( );
	auto end = subItems.end( );
	int left = space;
	int doubleTop = top * 2;
	int maxHeith = 0;
	for( ; iterator != end; ++iterator ) {
		auto widget = iterator.operator*( )->renderCurrentNodeFunctionWidget;
		widget->move( left, top );
		widget->show( );
		left = widget->width( ) + left + space;
		int height = widget->height( ) + doubleTop;
		if( maxHeith < height )
			maxHeith = height;
	}
	auto newSize = QSize( left, maxHeith );
	auto currentSize = itemWidget->size( );
	if( newSize != currentSize )
		itemWidget->setFixedSize( newSize );
	auto geometry = itemWidget->geometry( );
	QRect rect = contentsRect( );
	auto united = rect.united( geometry );
	newSize = united.size( );
	currentSize = this->size( );
	if( newSize != currentSize )
		setFixedSize( newSize );
	repaint( );
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {

	delete rootItem;
}
