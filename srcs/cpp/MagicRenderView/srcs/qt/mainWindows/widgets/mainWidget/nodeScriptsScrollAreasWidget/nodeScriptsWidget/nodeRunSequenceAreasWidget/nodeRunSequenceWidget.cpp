#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include "nodeRunSequenceWidget/nodeRunFunctionSequenceItemWidget.h"

NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	currentEextendItem = nullptr;
	itemSize = QSize( 50, 100 );
}
void NodeRunSequenceWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( this->contentsRect( ), Qt::darkGray );
}
NodeRunFunctionSequenceItemWidget * NodeRunSequenceWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {
	NodeRunFunctionSequenceItemWidget *posNode = nullptr;
	NodeRunFunctionSequenceItemWidget *resultItem = nullptr;
	QPoint fromGlobal = mapFromGlobal( glob_point );
	int height = itemSize.height( );
	int width = itemSize.width( );
	int fromGlobalX = fromGlobal.x( );
	// 是否匹配子节点
	bool isChild = false;
	if( fromGlobal.y( ) > height ) {
		if( currentEextendItem == nullptr )
			return nullptr;
		isChild = true;
	}
	resultItem = new NodeRunFunctionSequenceItemWidget( this, function_declaration );
	if( isChild ) {

	} else {
		// 匹配鼠标位置的项
		auto iterator = topItem.begin( );
		auto end = topItem.end( );

		if( iterator != end ) {
			int leftPos = 0;
			for( posNode = *iterator; iterator != end; ++iterator, posNode = *iterator, leftPos = posNode->pos( ).y( ) + width )
				if( leftPos > fromGlobalX )
					break;
			if( iterator == end ) {
				// 末尾
			} else {

			}
		}
	}

	if( resultItem->isItemActve( ) == false ) {
		delete resultItem;
		return nullptr;
	}
	// 配置插入位置

	// 链接信号
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::expandItem, [this, resultItem]( ) {
		expandItem( resultItem );
	} );
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::shrinkage, [this, resultItem]( ) {
		shrinkage( resultItem );
	} );
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::thisObjectDestory, [this, resultItem]( ) {
		removeItem( resultItem );
	} );
	// 更新面板
	updateNodeWidget( );
	return resultItem;
}
void NodeRunSequenceWidget::updateNodeWidget( ) {

}
bool NodeRunSequenceWidget::shrinkage( const NodeRunFunctionSequenceItemWidget *hide_item_widget ) {
	if( currentEextendItem != nullptr && hide_item_widget == nullptr )
		return false;
	else if( currentEextendItem == nullptr && currentEextendItem != hide_item_widget )
		return true;

	auto iterator = topItem.begin( );
	auto end = topItem.end( );
	NodeRunFunctionSequenceItemWidget *controlItemWidget = nullptr;
	do
		if( iterator == end )
			return false;
		else
			controlItemWidget = *( iterator++ );
	while( controlItemWidget != hide_item_widget );

	currentEextendItem = nullptr;
	controlItemWidget->showChildStatus = false;
	controlItemWidget->showStatusChange( controlItemWidget->showChildStatus );
	return true;
}
bool NodeRunSequenceWidget::removeItem( const NodeRunFunctionSequenceItemWidget *remove_item_widget ) {
	auto iterator = topItem.begin( );
	auto end = topItem.end( );
	for( ; iterator != end; ++iterator )
		if( *iterator == remove_item_widget ) {
			topItem.erase( iterator );
			return true;
		}
	return false;
}
bool NodeRunSequenceWidget::expandItem( const NodeRunFunctionSequenceItemWidget *show_item_widget ) {

	auto iterator = topItem.begin( );
	auto end = topItem.end( );
	NodeRunFunctionSequenceItemWidget *controlItemWidget = nullptr;
	do
		if( iterator == end )
			return false;
		else
			controlItemWidget = *iterator;
	while( controlItemWidget != show_item_widget );

	if( currentEextendItem == controlItemWidget )
		return true;

	// 屏蔽旧显示项
	if( currentEextendItem )
		if( shrinkage( currentEextendItem ) == false )
			return false;

	// 触发信号
	currentEextendItem = controlItemWidget;
	controlItemWidget->showStatusChange( controlItemWidget->showChildStatus );
	return true;
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {
}
