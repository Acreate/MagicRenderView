#include "uIntGenerateRenderWidget.h"

#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/uIntGenerateItemWidget.h"
#include "uIntGenerateRenderScrollArea.h"

UIntGenerateRenderWidget::UIntGenerateRenderWidget( UIntGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {
	dragItem = nullptr;
	intGenerateItemWidgetArratCount = 0;
	intGenerateItemWidgetArratPtr = nullptr;
}
void UIntGenerateRenderWidget::updateLayoutSort( ) {
	if( intGenerateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( intGenerateItemWidgetArratIndex = 0; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex ) {
		intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void UIntGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new UIntGenerateItemWidget( this );
	createWidgetItem->show( );
	intGenerateItemWidgetVector.insert( intGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	intGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	intGenerateItemWidgetArratCount = intGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void UIntGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( intGenerateItemWidgetArratCount <= index )
		return;
	intGenerateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void UIntGenerateRenderWidget::clear( ) {
	if( intGenerateItemWidgetArratCount == 0 )
		return;

	for( intGenerateItemWidgetArratIndex = 0; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex )
		delete intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ];
	intGenerateItemWidgetVector.clear( );
	intGenerateItemWidgetArratCount = 0;
	intGenerateItemWidgetArratPtr = nullptr;
}
void UIntGenerateRenderWidget::updateVectorIndex( ) {
	for( intGenerateItemWidgetArratIndex = 0; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex )
		intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->setIndex( intGenerateItemWidgetArratIndex );
}
void UIntGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( intGenerateItemWidgetArratCount == new_size )
		return;
	if( new_size > intGenerateItemWidgetArratCount ) {
		intGenerateItemWidgetVector.resize( new_size );
		intGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
		for( ; intGenerateItemWidgetArratCount < new_size; ++intGenerateItemWidgetArratCount ) {
			intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratCount ] = new UIntGenerateItemWidget( this );
			intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratCount ]->show( );
			intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		intGenerateItemWidgetArratIndex = new_size - 1;
		for( ; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex )
			delete intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ];
		intGenerateItemWidgetVector.resize( new_size );
		intGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	}
	intGenerateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > UIntGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( intGenerateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < intGenerateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = intGenerateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void UIntGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void UIntGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( intGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( intGenerateItemWidgetArratIndex = 0; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex )
					if( intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void UIntGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( intGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; intGenerateItemWidgetArratIndex < intGenerateItemWidgetArratCount; ++intGenerateItemWidgetArratIndex )
					if( intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = intGenerateItemWidgetArratPtr[ intGenerateItemWidgetArratIndex ]->getPopMenu( );
						if( popMenu == nullptr )
							return;
						popMenu->move( global );
						emit requesPopItemMenu_signal( popMenu );
						return;
					}
			}
			break;
		case Qt::LeftButton :
			if( dragItem == nullptr )
				break;
			dragItem = nullptr;
			updateLayoutSort( );
			break;
	}
}
