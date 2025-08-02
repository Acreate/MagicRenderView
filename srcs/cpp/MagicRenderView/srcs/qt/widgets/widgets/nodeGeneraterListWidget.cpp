#include "./nodeGeneraterListWidget.h"

#include "../widgetItem/nodeGeneraterItem.h"
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentContentFunStack = nullptr;
}
bool NodeGeneraterListWidget::setCurrentItem( const NodeGeneraterItem *fun_stack ) {
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
bool NodeGeneraterListWidget::appendItem( NodeGeneraterItem *fun_stack ) {
	fun_stack->setParent( this );
	return false;
}
NodeGeneraterItem * NodeGeneraterListWidget::appendFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	NodeGeneraterItem *generaterItem = new NodeGeneraterItem( fun_stack );
	bool item = appendItem( generaterItem );
	if( item )
		return generaterItem;
	delete generaterItem;
	return nullptr;
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
