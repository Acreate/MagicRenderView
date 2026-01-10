#include "imageGenerateRenderWidget.h"

#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/imageGenerateItemWidget.h"
#include "imageGenerateRenderScrollArea.h"

ImageGenerateRenderWidget::ImageGenerateRenderWidget( ImageGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {
	dragItem = nullptr;
	generateItemWidgetArratCount = 0;
	generateItemWidgetArratPtr = nullptr;
}
void ImageGenerateRenderWidget::updateLayoutSort( ) {
	if( generateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( generateItemWidgetArratIndex = 0; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex ) {
		generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void ImageGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new ImageGenerateItemWidget( this );
	createWidgetItem->show( );
	intGenerateItemWidgetVector.insert( intGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	generateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	generateItemWidgetArratCount = intGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void ImageGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( generateItemWidgetArratCount <= index )
		return;
	generateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void ImageGenerateRenderWidget::clear( ) {
	if( generateItemWidgetArratCount == 0 )
		return;

	for( generateItemWidgetArratIndex = 0; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex )
		delete generateItemWidgetArratPtr[ generateItemWidgetArratIndex ];
	intGenerateItemWidgetVector.clear( );
	generateItemWidgetArratCount = 0;
	generateItemWidgetArratPtr = nullptr;
}
void ImageGenerateRenderWidget::updateVectorIndex( ) {
	for( generateItemWidgetArratIndex = 0; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex )
		generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->setIndex( generateItemWidgetArratIndex );
}
void ImageGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( generateItemWidgetArratCount == new_size )
		return;
	if( new_size > generateItemWidgetArratCount ) {
		intGenerateItemWidgetVector.resize( new_size );
		generateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
		for( ; generateItemWidgetArratCount < new_size; ++generateItemWidgetArratCount ) {
			generateItemWidgetArratPtr[ generateItemWidgetArratCount ] = new ImageGenerateItemWidget( this );
			generateItemWidgetArratPtr[ generateItemWidgetArratCount ]->show( );
			generateItemWidgetArratPtr[ generateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		generateItemWidgetArratIndex = new_size - 1;
		for( ; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex )
			delete generateItemWidgetArratPtr[ generateItemWidgetArratIndex ];
		intGenerateItemWidgetVector.resize( new_size );
		generateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	}
	generateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > ImageGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( generateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < generateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = generateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void ImageGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void ImageGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( generateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( generateItemWidgetArratIndex = 0; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex )
					if( generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = generateItemWidgetArratPtr[ generateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void ImageGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( generateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; generateItemWidgetArratIndex < generateItemWidgetArratCount; ++generateItemWidgetArratIndex )
					if( generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = generateItemWidgetArratPtr[ generateItemWidgetArratIndex ]->getPopMenu( );
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
