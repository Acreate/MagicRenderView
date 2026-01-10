#include "charGenerateRenderWidget.h"

#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/charGenerateItemWidget.h"
#include "charGenerateRenderScrollArea.h"

CharGenerateRenderWidget::CharGenerateRenderWidget( CharGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {
	dragItem = nullptr;
	charGenerateItemWidgetArratCount = 0;
	charGenerateItemWidgetArratPtr = nullptr;
}
void CharGenerateRenderWidget::updateLayoutSort( ) {
	if( charGenerateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( charGenerateItemWidgetArratIndex = 0; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex ) {
		charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void CharGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new CharGenerateItemWidget( this );
	createWidgetItem->show( );
	intGenerateItemWidgetVector.insert( intGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	charGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	charGenerateItemWidgetArratCount = intGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void CharGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( charGenerateItemWidgetArratCount <= index )
		return;
	charGenerateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void CharGenerateRenderWidget::clear( ) {
	if( charGenerateItemWidgetArratCount == 0 )
		return;

	for( charGenerateItemWidgetArratIndex = 0; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex )
		delete charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ];
	intGenerateItemWidgetVector.clear( );
	charGenerateItemWidgetArratCount = 0;
	charGenerateItemWidgetArratPtr = nullptr;
}
void CharGenerateRenderWidget::updateVectorIndex( ) {
	for( charGenerateItemWidgetArratIndex = 0; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex )
		charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->setIndex( charGenerateItemWidgetArratIndex );
}
void CharGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( charGenerateItemWidgetArratCount == new_size )
		return;
	if( new_size > charGenerateItemWidgetArratCount ) {
		intGenerateItemWidgetVector.resize( new_size );
		charGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
		for( ; charGenerateItemWidgetArratCount < new_size; ++charGenerateItemWidgetArratCount ) {
			charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratCount ] = new CharGenerateItemWidget( this );
			charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratCount ]->show( );
			charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		charGenerateItemWidgetArratIndex = new_size - 1;
		for( ; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex )
			delete charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ];
		intGenerateItemWidgetVector.resize( new_size );
		charGenerateItemWidgetArratPtr = intGenerateItemWidgetVector.data( );
	}
	charGenerateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > CharGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( charGenerateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < charGenerateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = charGenerateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void CharGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void CharGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( charGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( charGenerateItemWidgetArratIndex = 0; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex )
					if( charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void CharGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( charGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; charGenerateItemWidgetArratIndex < charGenerateItemWidgetArratCount; ++charGenerateItemWidgetArratIndex )
					if( charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = charGenerateItemWidgetArratPtr[ charGenerateItemWidgetArratIndex ]->getPopMenu( );
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
