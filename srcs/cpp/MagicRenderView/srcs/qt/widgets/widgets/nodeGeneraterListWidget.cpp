#include "./nodeGeneraterListWidget.h"

#include "../widgetItem/nodeGeneraterItem.h"
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentItem = nullptr;
}
NodeGeneraterListWidget::~NodeGeneraterListWidget( ) {
	for( auto item : funStackItemS )
		delete item;
}
bool NodeGeneraterListWidget::setCurrentItem( const NodeGeneraterItem *item ) {
	for( auto &fItem : funStackItemS )
		if( fItem == item ) {
			return true;
		}
	return false;
}
const NodeGeneraterItem * NodeGeneraterListWidget::setCurrentFunStackIndex( const size_t &fun_stack_index ) {
	size_t count = funStackItemS.size( );
	if( fun_stack_index >= count )
		return nullptr;
	auto data = funStackItemS.data( );
	currentItem = data[ fun_stack_index ];
	return currentItem;
}
std_shared_ptr< IFunStack > NodeGeneraterListWidget::getCurrentFunStack( ) const {
	if( currentItem == nullptr )
		return nullptr;
	return currentItem->getFunStack( );
}
size_t NodeGeneraterListWidget::getCurrentFunStackIndex( ) const {
	size_t count = funStackItemS.size( );
	auto data = funStackItemS.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == currentItem )
			return index;
	return count;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendItem( NodeGeneraterItem *item ) {
	for( auto &fItem : funStackItemS )
		if( fItem == item )
			return item;
	funStackItemS.emplace_back( item );
	return item;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return appendItem( new NodeGeneraterItem( fun_stack ) );
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
