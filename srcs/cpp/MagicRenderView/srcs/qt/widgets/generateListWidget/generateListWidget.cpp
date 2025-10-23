#include <QPainter>
#include <QScrollBar>

#include "GenerateListItemWidget.h"
#include "GenerateListWidget.h"
#include "generateAddInfoWidget.h"
#include "generateListScrollArea.h"
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
	int x = 0, y = 0, offset = 2;
	generateAddInfoWidget->move( offset, y );
	int width = generateAddInfoWidget->width( );
	if( width > x )
		x = width;
	y += generateAddInfoWidget->height( );
	if( count == 0 ) {
		generateAddInfoWidget->setFixedWidth( x + offset );
		setFixedSize( x + offset, y );
		generateListScrollArea->setFixedSize( x + verticalScrollBar->width( ) + offset * 2, y + horizontalScrollBar->height( ) + offset );
		return true;
	}
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) { // 停止，并且重置所有宽度
			count = index + 1;
			index = 0;
			for( ; index < count; ++index )
				data[ index ]->setFixedWidth( x + offset );
			generateAddInfoWidget->setFixedWidth( x + offset );
			break;
		} else {
			data[ index ]->move( offset, y );
			width = data[ index ]->width( );
			if( width > x )
				x = width;
			y += data[ index ]->height( );

		}
	setFixedSize( x + offset, y );
	generateListScrollArea->setFixedSize( x + verticalScrollBar->width( ) + offset * 2, y + horizontalScrollBar->height( ) + offset );
	return true;
}
GenerateListWidget::GenerateListWidget( GenerateListScrollArea *parent ) : QWidget( parent ) {
	generateAddInfoWidget = new GenerateAddInfoWidget( this );
	generateAddInfoWidget->move( 0, 0 );
	generateListScrollArea = parent;
	generateListScrollArea->setWidget( this );
	generateListScrollArea->setWidgetResizable( true );
	generateListScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	generateListScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	horizontalScrollBar = generateListScrollArea->horizontalScrollBar( );
	verticalScrollBar = generateListScrollArea->verticalScrollBar( );
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
void GenerateListWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	sortItemWidget( );
}
