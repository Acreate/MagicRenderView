#include "./nodeGeneraterListWidget.h"

#include "../../functionDeclaration/IFunctionDeclaration.h"

#include "../../stacks/funStack/IFunStack.h"

#include "../widgetItem/nodeGeneraterItem.h"
const NodeGeneraterItem * NodeGeneraterListWidget::setCurrentIndex( const size_t &fun_stack_index ) {
	auto data = funStackItemS.data( );
	currentItem = data[ fun_stack_index ].first;
	// todo : 配置活动窗口
	return currentItem;
}
std_pairt< NodeGeneraterItem *, QWidget * > NodeGeneraterListWidget::generaterItemWidget( NodeGeneraterItem *node_item ) {

	std_pairt< NodeGeneraterItem *, QWidget * > result { nullptr, nullptr };
	// 检测选项是否正确，正确生成窗口
	if( node_item == nullptr )
		return result;
	// todo : 生成主要窗口
	QWidget *widget = new QWidget( this );
	widget->hide( );

	
	
	result.first = node_item;
	result.second = widget;

	// 检查函数数量，填充函数功能到窗口
	IFunStack *element = node_item->getFunStack( ).get( );
	auto functionDeclarations = element->getGenerFunctions( );
	size_t count = functionDeclarations.size( );
	if( count == 0 )
		return result;
	auto declarationPtr = functionDeclarations.data( );
	IFunctionDeclaration *functionElement;
	size_t index = 0;
	for( functionElement = declarationPtr[ index ].get( ); index < count; ++index, functionElement = declarationPtr[ index ].get( ) )
		if( functionElement->isIsValid( ) == true ) {
			// todo : 生成窗口控件
		}

	return result;
}
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentItem = nullptr;
}
NodeGeneraterListWidget::~NodeGeneraterListWidget( ) {
	for( auto item : funStackItemS ) {
		delete item.first;
		delete item.second;
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
std_shared_ptr< IFunStack > NodeGeneraterListWidget::getCurrentFunStack( ) const {
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
	if( currentItem == nullptr )
		setCurrentIndex( 0 );
	return item;
}
const NodeGeneraterItem * NodeGeneraterListWidget::appendFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return appendItem( new NodeGeneraterItem( fun_stack ) );
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
