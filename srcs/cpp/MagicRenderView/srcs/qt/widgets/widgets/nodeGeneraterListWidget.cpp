#include "./nodeGeneraterListWidget.h"

#include "../widgetItem/nodeGeneraterItem.h"
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentContentFunStack = nullptr;
}
NodeGeneraterListWidget::~NodeGeneraterListWidget( ) {
	for( auto item : funStackItemS )
		delete item;
}
bool NodeGeneraterListWidget::setCurrentItem( const NodeGeneraterItem *item ) {
	return false;
}
bool NodeGeneraterListWidget::setCurrentFunStackIndex( const size_t &fun_stack_index ) {
	return false;
}
std_shared_ptr< IFunStack > NodeGeneraterListWidget::getCurrentFunStack( ) const {
	return currentContentFunStack->getFunStack( );
}
size_t NodeGeneraterListWidget::getCurrentFunStackIndex( ) const {
	size_t count = funStackItemS.size( );
	auto data = funStackItemS.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == currentContentFunStack )
			return index;
	return count;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendItem( const NodeGeneraterItem &item ) {
	return false;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return appendItem( fun_stack );
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
