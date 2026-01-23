#include "previewImageContentWidget.h"

#include <node/node/node.h>
#include <qlayout.h>

#include "../../../debugNodes/view/previewImageNode.h"
#include "outImagePortItemScrollArea/imageOutPortItemScrollArea.h"
#include "outImagePortItemScrollArea/imageOutPortItemScrollWidget.h"
#include "toolWidget/imageOutPortContentToolsWidget.h"

PreviewImageContentWidget::PreviewImageContentWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	tool = new ImageOutPortContentToolsWidget( this );
	tool->move( 0, 0 );
	imageOutPortItemScrollArea = new ImageOutPortItemScrollArea( this );
	imageOutPortItemScrollWidget = imageOutPortItemScrollArea->getImageOutPortItemScrollWidget( );
	connect( tool, &ImageOutPortContentToolsWidget::click_builder_target_signal, this, &PreviewImageContentWidget::click_builder_target_signal );
}
bool PreviewImageContentWidget::init( PreviewImageNode *node ) {
	if( node == nullptr )
		return false;
	tool->setTargetNode( node );
	return true;
}
bool PreviewImageContentWidget::updateLayout( ) {
	int maxWidth = this->width( );
	int maxHeiht = this->height( );
	int toolHeight = tool->height( );
	tool->setFixedWidth( maxWidth );
	imageOutPortItemScrollArea->move( 0, toolHeight );
	maxHeiht = maxHeiht - toolHeight;
	imageOutPortItemScrollArea->setFixedSize( maxWidth, maxHeiht );
	return true;
}
void PreviewImageContentWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
