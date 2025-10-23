#include <QPainter>

#include "GenerateListItemWidget.h"
#include "GenerateListWidget.h"
#include "generateAddInfoWidget.h"
bool GenerateListWidget::addItem( GenerateListItemWidget *new_list_item_widget ) {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == new_list_item_widget )
			return true;
		else if( data[ index ] == nullptr ) {
			data[ index ] = new_list_item_widget;
			return true;
		}
	generateListItemWidgets.emplace_back( new_list_item_widget );
	return false;
}
bool GenerateListWidget::removeItem( const GenerateListItemWidget *new_list_item_widget ) {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == new_list_item_widget ) {
			delete data[ index ];
			++index;
			for( ; index < count; ++index )
				data[ index - 1 ] = data[ index ];
			return true;
		}
	return false;
}
bool GenerateListWidget::inster( GenerateListItemWidget *new_list_item_widget, const size_t &index ) {
	size_t count = generateListItemWidgets.size( );
	if( count <= index )
		return false;
	auto data = generateListItemWidgets.data( );
	size_t foreachIndex = 0;
	for( ; foreachIndex < count; ++foreachIndex )
		if( data[ foreachIndex ] == nullptr )
			return false; // 不在管理内
		else if( data[ foreachIndex ] == new_list_item_widget ) {
			if( foreachIndex == index )
				return true;
			if( foreachIndex < index ) {
				for( ; foreachIndex > index; --foreachIndex )
					data[ foreachIndex ] = data[ foreachIndex - 1 ];
				data[ index ] = new_list_item_widget;
				return true;
			}
			for( ; foreachIndex < index; ++foreachIndex )
				data[ foreachIndex ] = data[ foreachIndex + 1 ];
			data[ index ] = new_list_item_widget;
			return true;
		}

	return true;
}
bool GenerateListWidget::sortItemWidget( ) {
	size_t count = generateListItemWidgets.size( );
	if( count == 0 )
		return true;
	int x = 0, y = 0;
	generateAddInfoWidget->move( x, y );
	int width = generateAddInfoWidget->width( );
	if( width > x )
		x = width;
	y += generateAddInfoWidget->height( );
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else {
			data[ index ]->move( 0, y );
			width = data[ index ]->width( );
			if( width > x )
				x = width;
			y += data[ index ]->height( );
		}
	setMinimumSize( x, y );
	return true;
}
GenerateListWidget::GenerateListWidget( QWidget *parent ) : QWidget( parent ) {
	generateAddInfoWidget = new GenerateAddInfoWidget( this );
	generateAddInfoWidget->move( 0, 0 );
	setMinimumSize( generateAddInfoWidget->size( ) );
}
GenerateListWidget::~GenerateListWidget( ) {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else
			delete data[ index ];
	generateListItemWidgets.clear( );
}
std_vector< std_shared_ptr< I_Var > > GenerateListWidget::getItemVarVector( ) const {
	std_vector< std_shared_ptr< I_Var > > result;
	size_t count = generateListItemWidgets.size( );
	if( count == 0 )
		return result;
	auto data = generateListItemWidgets.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else
			result.emplace_back( data[ index ]->getVar( ) );
	return result;
}
std_shared_ptr< I_Var > GenerateListWidget::getItemIndexVar( const size_t &index ) const {
	std_vector< std_shared_ptr< I_Var > > result;
	size_t count = generateListItemWidgets.size( );
	if( count <= index )
		return nullptr;
	auto data = generateListItemWidgets.data( );
	if( data[ index ] == nullptr )
		return nullptr;
	return data[ index ]->getVar( );
}
void GenerateListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );

}
