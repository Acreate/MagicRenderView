#include "floatGenerateRenderWidget.h"

#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/floatGenerateItemWidget.h"
#include "floatGenerateRenderScrollArea.h"

FloatGenerateRenderWidget::FloatGenerateRenderWidget( FloatGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ),
	generateRenderScrollArea( generate_render_scroll_area ) {

	dragItem = nullptr;
	floatGenerateItemWidgetArratCount = 0;
	floatGenerateItemWidgetArratPtr = nullptr;
}
void FloatGenerateRenderWidget::updateLayoutSort( ) {
	if( floatGenerateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( floatGenerateItemWidgetArratIndex = 0; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex ) {
		floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void FloatGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new FloatGenerateItemWidget( this );
	createWidgetItem->show( );
	intGenerateItemWidgetVector.insert( intGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	floatGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	floatGenerateItemWidgetArratCount = intGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void FloatGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( floatGenerateItemWidgetArratCount <= index )
		return;
	floatGenerateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void FloatGenerateRenderWidget::clear( ) {
	if( floatGenerateItemWidgetArratCount == 0 )
		return;

	for( floatGenerateItemWidgetArratIndex = 0; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex )
		delete floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ];
	intGenerateItemWidgetVector.clear( );
	floatGenerateItemWidgetArratCount = 0;
	floatGenerateItemWidgetArratPtr = nullptr;
}
void FloatGenerateRenderWidget::updateVectorIndex( ) {
	for( floatGenerateItemWidgetArratIndex = 0; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex )
		floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->setIndex( floatGenerateItemWidgetArratIndex );
}
void FloatGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( floatGenerateItemWidgetArratCount == new_size )
		return;
	if( new_size > floatGenerateItemWidgetArratCount ) {
		intGenerateItemWidgetVector.resize( new_size );
		floatGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
		for( ; floatGenerateItemWidgetArratCount < new_size; ++floatGenerateItemWidgetArratCount ) {
			floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratCount ] = new FloatGenerateItemWidget( this );
			floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratCount ]->show( );
			floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		floatGenerateItemWidgetArratIndex = new_size - 1;
		for( ; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex )
			delete floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ];
		intGenerateItemWidgetVector.resize( new_size );
		floatGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	}
	floatGenerateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > FloatGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( floatGenerateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < floatGenerateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = floatGenerateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void FloatGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void FloatGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( floatGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( floatGenerateItemWidgetArratIndex = 0; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex )
					if( floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void FloatGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( floatGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; floatGenerateItemWidgetArratIndex < floatGenerateItemWidgetArratCount; ++floatGenerateItemWidgetArratIndex )
					if( floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = floatGenerateItemWidgetArratPtr[ floatGenerateItemWidgetArratIndex ]->getPopMenu( );
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
