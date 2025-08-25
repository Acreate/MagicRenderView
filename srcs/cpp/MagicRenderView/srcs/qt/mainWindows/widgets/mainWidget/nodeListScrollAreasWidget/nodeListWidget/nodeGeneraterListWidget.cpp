#include "./nodeGeneraterListWidget.h"

#include <qevent.h>

#include "nodeGeneraterItem.h"

#include "nodeGeneraterListWidget/nodePreviewScrollAreasWidget.h"

const NodeGeneraterItem * NodeGeneraterListWidget::setCurrentIndex( const size_t &fun_stack_index ) {
	auto data = funStackItemS.data( );
	if( currentItem )
		NodeGeneraterItemGenerater::getRenderWidget( currentItem )->hide( );
	currentItem = data[ fun_stack_index ].first;
	QWidget * renderWidget = NodeGeneraterItemGenerater::getRenderWidget( currentItem );
	auto currentSize = contentsRect( ).size( );
	renderWidget->setFixedSize( currentSize );
	renderWidget->show( );
	return currentItem;
}
std_pairt< NodeGeneraterItem *, NodePreviewScrollAreasWidget * > NodeGeneraterListWidget::generaterItemWidget( NodeGeneraterItem *node_item ) {

	std_pairt< NodeGeneraterItem *, NodePreviewScrollAreasWidget * > result { nullptr, nullptr };
	// 检测选项是否正确，正确生成窗口
	if( node_item == nullptr )
		return result;
	// todo : 生成主要窗口
	NodePreviewScrollAreasWidget *widget = new NodePreviewScrollAreasWidget( this );

	if( widget->setFunStack( NodeGeneraterItemGenerater::getFunStack( node_item ) ) == false ) {
		delete widget;
		return result;
	}

	result.first = node_item;
	result.second = widget;

	return result;
}
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentItem = nullptr;
}
NodeGeneraterListWidget::~NodeGeneraterListWidget( ) {
	for( auto item : funStackItemS ) {
		auto renderWidget = NodeGeneraterItemGenerater::getRenderWidget( item.first );
		if( renderWidget != item.second )
			delete item.second;
		delete item.first;
	}
}
bool NodeGeneraterListWidget::setCurrentItem( const NodeGeneraterItem *item ) {
	size_t count = funStackItemS.size( );
	if( count == 0 )
		return false;
	auto nodeGeneraterItemPtr = funStackItemS.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeGeneraterItemPtr[ index ].first == item )
			return setCurrentIndex( index ) != nullptr;
	return false;
}
const NodeGeneraterItem * NodeGeneraterListWidget::setCurrentFunStackIndex( const size_t &fun_stack_index ) {
	size_t count = funStackItemS.size( );
	if( fun_stack_index >= count )
		return nullptr;
	return setCurrentIndex( fun_stack_index );
}
const IFunStack * NodeGeneraterListWidget::getCurrentFunStack( ) const {
	if( currentItem == nullptr )
		return nullptr;
	return currentItem->getFunStack( );
}
size_t NodeGeneraterListWidget::getCurrentFunStackIndex( ) const {
	size_t count = funStackItemS.size( );
	auto data = funStackItemS.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == currentItem )
			return index;
	return count;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendItem( NodeGeneraterItem *item ) {
	for( auto &fItem : funStackItemS )
		if( fItem.first == item )
			return item;
	auto itemWidget = generaterItemWidget( item );
	if( itemWidget.first == nullptr )
		return nullptr;
	funStackItemS.emplace_back( itemWidget );
	NodeGeneraterItemGenerater::setRenderWidget( item, itemWidget.second );
	itemWidget.second->setFixedSize( contentsRect( ).size( ) );

	if( currentItem == nullptr )
		setCurrentIndex( 0 );
	return item;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return appendItem( NodeGeneraterItemGenerater::generaterItem( fun_stack ) );
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	if( currentItem == nullptr )
		return;
	auto currentSize = contentsRect( ).size( );
	NodeGeneraterItemGenerater::getRenderWidget( currentItem )->setFixedSize( currentSize );
}
