#include "stringGenerateRenderWidget.h"


#include <QMenu>
#include <QMouseEvent>

#include "../generateItemWidget/stringGenerateItemWidget.h"
#include "stringGenerateRenderScrollArea.h"

StringGenerateRenderWidget::StringGenerateRenderWidget( StringGenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {
	dragItem = nullptr;
	stringGenerateItemWidgetArratCount = 0;
	stringGenerateItemWidgetArratPtr = nullptr;
}
void StringGenerateRenderWidget::updateLayoutSort( ) {
	if( stringGenerateItemWidgetArratCount == 0 )
		return;
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	for( stringGenerateItemWidgetArratIndex = 0; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex ) {
		stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->move( 0, offsetY );
		viewWidth = stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->height( );

	}
	setMinimumSize( currentWidth, offsetY );
}
void StringGenerateRenderWidget::createItem( const size_t &index ) {
	auto createWidgetItem = new StringGenerateItemWidget( this );
	createWidgetItem->show( );
	stringGenerateItemWidgetVector.insert( stringGenerateItemWidgetVector.begin( ) + index, createWidgetItem );
	stringGenerateItemWidgetArratPtr = stringGenerateItemWidgetVector.data( );
	stringGenerateItemWidgetArratCount = stringGenerateItemWidgetVector.size( );
	updateLayoutSort( );
}
void StringGenerateRenderWidget::setInfo( const size_t &index, const QString &var_value ) {
	if( stringGenerateItemWidgetArratCount <= index )
		return;
	stringGenerateItemWidgetArratPtr[ index ]->setInfo( index, var_value );
}
void StringGenerateRenderWidget::clear( ) {
	if( stringGenerateItemWidgetArratCount == 0 )
		return;

	for( stringGenerateItemWidgetArratIndex = 0; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex )
		delete stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ];
	stringGenerateItemWidgetVector.clear( );
	stringGenerateItemWidgetArratCount = 0;
	stringGenerateItemWidgetArratPtr = nullptr;
}
void StringGenerateRenderWidget::updateVectorIndex( ) {
	for( stringGenerateItemWidgetArratIndex = 0; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex )
		stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->setIndex( stringGenerateItemWidgetArratIndex );
}
void StringGenerateRenderWidget::resize( const size_t &new_size ) {
	if( new_size == 0 ) {
		clear( );
		return;
	}
	if( stringGenerateItemWidgetArratCount == new_size )
		return;
	if( new_size > stringGenerateItemWidgetArratCount ) {
		stringGenerateItemWidgetVector.resize( new_size );
		stringGenerateItemWidgetArratPtr = stringGenerateItemWidgetVector.data( );
		for( ; stringGenerateItemWidgetArratCount < new_size; ++stringGenerateItemWidgetArratCount ) {
			stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratCount ] = new StringGenerateItemWidget( this );
			stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratCount ]->show( );
			stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratCount ]->setParent( this );
		}
	} else {
		stringGenerateItemWidgetArratIndex = new_size - 1;
		for( ; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex )
			delete stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ];
		stringGenerateItemWidgetVector.resize( new_size );
		stringGenerateItemWidgetArratPtr = stringGenerateItemWidgetVector.data( );
	}
	stringGenerateItemWidgetArratCount = new_size;
	updateLayoutSort( );
}
std::vector< QString > StringGenerateRenderWidget::converTextVector( ) const {
	std::vector< QString > result( stringGenerateItemWidgetArratCount );
	auto resultStringArrayPtr = result.data( );
	auto index = 0;
	for( ; index < stringGenerateItemWidgetArratCount; ++index )
		resultStringArrayPtr[ index ] = stringGenerateItemWidgetArratPtr[ index ]->getVarValue( );
	return result;
}
void StringGenerateRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( dragItem ) { }
}
void StringGenerateRenderWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton : {
			if( stringGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( stringGenerateItemWidgetArratIndex = 0; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex )
					if( stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						dragItem = stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ];
						break;
					}
			}
			break;
		}
	}
}
void StringGenerateRenderWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( stringGenerateItemWidgetArratCount != 0 ) {
				QPoint global;
				QPoint fromGlobal;
				global = QCursor::pos( );
				fromGlobal = mapFromGlobal( global );
				for( ; stringGenerateItemWidgetArratIndex < stringGenerateItemWidgetArratCount; ++stringGenerateItemWidgetArratIndex )
					if( stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->isDragWidgetPos( fromGlobal ) ) {
						auto popMenu = stringGenerateItemWidgetArratPtr[ stringGenerateItemWidgetArratIndex ]->getPopMenu( );
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
