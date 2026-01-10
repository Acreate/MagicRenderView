#include "binGenerateRenderWidget.h"

#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/binGenerateItemWidget.h"
#include "binGenerateRenderScrollArea.h"

BinGenerateRenderWidget::BinGenerateRenderWidget( BinGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {
	dragItem = nullptr;
	binGenerateItemWidgetArratCount = 0;
	binGenerateItemWidgetArratPtr = nullptr;
}
void BinGenerateRenderWidget::updateLayoutSort( ) {
	if( binGenerateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( binGenerateItemWidgetArratIndex = 0; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex ) {
		binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void BinGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new BinGenerateItemWidget( this );
	createWidgetItem->show( );
	binGenerateItemWidgetVector.insert( binGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	binGenerateItemWidgetArratPtr = binGenerateItemWidgetVector.data( );
	binGenerateItemWidgetArratCount = binGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void BinGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( binGenerateItemWidgetArratCount <= index )
		return;
	binGenerateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void BinGenerateRenderWidget::clear( ) {
	if( binGenerateItemWidgetArratCount == 0 )
		return;

	for( binGenerateItemWidgetArratIndex = 0; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex )
		delete binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ];
	binGenerateItemWidgetVector.clear( );
	binGenerateItemWidgetArratCount = 0;
	binGenerateItemWidgetArratPtr = nullptr;
}
void BinGenerateRenderWidget::updateVectorIndex( ) {
	for( binGenerateItemWidgetArratIndex = 0; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex )
		binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->setIndex( binGenerateItemWidgetArratIndex );
}
void BinGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( binGenerateItemWidgetArratCount == new_size )
		return;
	if( new_size > binGenerateItemWidgetArratCount ) {
		binGenerateItemWidgetVector.resize( new_size );
		binGenerateItemWidgetArratPtr = binGenerateItemWidgetVector.data( );
		for( ; binGenerateItemWidgetArratCount < new_size; ++binGenerateItemWidgetArratCount ) {
			binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratCount ] = new BinGenerateItemWidget( this );
			binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratCount ]->show( );
			binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		binGenerateItemWidgetArratIndex = new_size - 1;
		for( ; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex )
			delete binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ];
		binGenerateItemWidgetVector.resize( new_size );
		binGenerateItemWidgetArratPtr = binGenerateItemWidgetVector.data( );
	}
	binGenerateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > BinGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( binGenerateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < binGenerateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = binGenerateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void BinGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void BinGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( binGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( binGenerateItemWidgetArratIndex = 0; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex )
					if( binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void BinGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( binGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; binGenerateItemWidgetArratIndex < binGenerateItemWidgetArratCount; ++binGenerateItemWidgetArratIndex )
					if( binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = binGenerateItemWidgetArratPtr[ binGenerateItemWidgetArratIndex ]->getPopMenu( );
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
