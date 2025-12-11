#include "generateRenderWidget.h"

#include "../generateItemWidget/generateItemWidget.h"
#include "generateRenderScrollArea.h"
GenerateRenderWidget::GenerateRenderWidget( GenerateRenderScrollArea *generate_render_scroll_area ) : QWidget( generate_render_scroll_area ), generateRenderScrollArea( generate_render_scroll_area ) {

}
void GenerateRenderWidget::updateLayoutSort( ) {
	int offsetY = 0;
	int viewWidth;
	int currentWidth = this->width( );
	size_t count = intGenerateItemWidgetVector.size( );
	auto generateItemWidgetArrayPtr = intGenerateItemWidgetVector.data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		if( generateItemWidgetArrayPtr[ index ]->isHidden( ) ) {
			generateItemWidgetArrayPtr[ index ]->setParent( this );
			generateItemWidgetArrayPtr[ index ]->show( );
		}
		generateItemWidgetArrayPtr[ index ]->move( 0, offsetY );
		viewWidth = generateItemWidgetArrayPtr[ index ]->width( );
		if( viewWidth > currentWidth )
			currentWidth = viewWidth;
		offsetY += generateItemWidgetArrayPtr[ index ]->height( );

	}
	setFixedSize( currentWidth, offsetY );
}
