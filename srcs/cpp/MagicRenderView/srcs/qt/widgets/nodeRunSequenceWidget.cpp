#include "./nodeRunSequenceWidget.h"

#include <QPainter>

#include "nodeRunFunctionSequenceItemWidget.h"

NodeRunSequenceWidget::NodeRunSequenceWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	currentEextendItem = nullptr;
	itemWidth = 200;
	itemHeight = 100;
	itemSpaceWidth = 20;
	itemSpaceHeight = 20;
}
void NodeRunSequenceWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto pen = painter.pen( );
	int penWidth = 4;
	pen.setWidth( penWidth );
	penWidth *= 2;
	pen.setColor( Qt::GlobalColor::darkBlue );
	painter.setPen( pen );
	painter.drawRect( 0, 0, width( ) - penWidth, height( ) - penWidth );
}
void NodeRunSequenceWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateExpandItem( );
}
NodeRunFunctionSequenceItemWidget * NodeRunSequenceWidget::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {

	// 转换到本地位置
	QPoint fromGlobal = mapFromGlobal( glob_point );
	// 是否匹配子节点
	if( fromGlobal.y( ) > itemHeight ) {
		if( currentEextendItem == nullptr )
			return nullptr;
		NodeRunSequenceWidget *itemChild = currentEextendItem->getItemChild( );
		if( itemChild == nullptr || itemChild->isHidden( ) )
			return nullptr;
		return itemChild->setRunFunctionWidget( generater_scripts_widget, function_declaration, glob_point, set_point );
	}

	NodeRunFunctionSequenceItemWidget *posNode = nullptr;
	NodeRunFunctionSequenceItemWidget *resultItem = nullptr;
	int fromGlobalX = fromGlobal.x( );
	resultItem = new NodeRunFunctionSequenceItemWidget( this, function_declaration );
	if( resultItem->isItemActve( ) == false ) {
		delete resultItem;
		return nullptr;
	}
	resultItem->setFixedSize( itemWidth, itemHeight );
	// 匹配鼠标位置的项
	auto begin = topItem.begin( );
	auto iterator = begin;
	auto end = topItem.end( );

	if( iterator != end ) {
		// 窗口的右侧坐标
		int nodeRightXPos = 0;
		for( ; iterator != end; ++iterator )
			if( posNode = *iterator, nodeRightXPos = posNode->pos( ).x( ) + itemWidth, nodeRightXPos > fromGlobalX )
				break;
		topItem.insert( iterator, resultItem );
	} else
		topItem.emplace_back( resultItem );
	// 链接信号
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::expandItem, [this, resultItem]( ) {
		expandItem( resultItem );
	} );
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::doubleClick, resultItem, &NodeRunFunctionSequenceItemWidget::expandItem );
	connect( resultItem, &NodeRunFunctionSequenceItemWidget::shrinkage, [this, resultItem]( ) {
		shrinkage( resultItem );
	} );
	// 更新面板
	updateNodeWidget( );
	return resultItem;

}
void NodeRunSequenceWidget::updateNodeWidget( ) {

	auto iterator = topItem.begin( );
	auto end = topItem.end( );
	// 窗口的右侧坐标
	int nodeRightXPos = 0;
	for( ; iterator != end; ++iterator ) {
		auto node = *iterator;
		node->show( );
		node->move( nodeRightXPos, 0 );
		nodeRightXPos += itemWidth + itemSpaceWidth;
	}

	updateExpandItem( );
	// todo : 最小大小
}
bool NodeRunSequenceWidget::shrinkage( const NodeRunFunctionSequenceItemWidget *hide_item_widget ) {
	if( currentEextendItem != nullptr && hide_item_widget == nullptr )
		return false;
	else if( currentEextendItem == nullptr && hide_item_widget )
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

	auto itemChild = currentEextendItem->getItemChild( );
	if( itemChild )
		itemChild->hide( );
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
void NodeRunSequenceWidget::updateExpandItem( ) {
	if( currentEextendItem == nullptr )
		return;
	NodeRunSequenceWidget *itemChild = currentEextendItem->getItemChild( );
	if( itemChild == nullptr )
		return;
	if( itemChild->isHidden( ) == false )
		itemChild->show( );
	auto currentWidgetSize = this->size( );
	int currentItemHeight = currentWidgetSize.height( );
	itemChild->move( 0, currentItemHeight + itemSpaceHeight );
	int height = currentEextendItem->size( ).height( );
	itemChild->setFixedSize( currentWidgetSize.width( ), currentItemHeight - height );
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

	currentEextendItem = controlItemWidget;
	NodeRunSequenceWidget *itemChild = currentEextendItem->getItemChild( );
	itemChild->show( );
	updateExpandItem( );
	// 触发信号
	currentEextendItem->showStatusChange( currentEextendItem->showChildStatus );
	return true;
}
NodeRunSequenceWidget::~NodeRunSequenceWidget( ) {
	std_vector< NodeRunFunctionSequenceItemWidget * > release( topItem.begin( ), topItem.end( ) );
	topItem.clear( );
	size_t count = release.size( );
	auto data = release.data( );
	for( size_t index = 0; index < count; ++index ) {
		NodeRunFunctionSequenceItemWidget *itemWidget = data[ index ];
		itemWidget->setParent( this );
		itemWidget->itemParent = this;
		delete itemWidget;
	}
}
