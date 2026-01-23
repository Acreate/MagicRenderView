#include "debugNodeContentWidget.h"

#include <node/node/node.h>
#include <qlayout.h>

#include "../../../debugNodes/outInfo/debugInfoNode.h"
#include "outPortItemScrollArea/outPortItemScrollArea.h"
#include "outPortItemScrollArea/outPortItemScrollWidget.h"

#include "toolWidget/debugNodeContentToolsWidget.h"

DebugNodeContentWidget::DebugNodeContentWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	tool = new DebugNodeContentToolsWidget( this );
	tool->move( 0, 0 );
	outputItemScrollArea = new OutPortItemScrollArea( this );
	outPortItemScrollWidget = outputItemScrollArea->getOutPortItemScrollWidget( );
	connect( tool, &DebugNodeContentToolsWidget::click_builder_target_signal, this, &DebugNodeContentWidget::click_builder_target_signal );
}
bool DebugNodeContentWidget::init( DebugInfoNode *node ) {
	if( node == nullptr )
		return false;
	tool->setTargetNode( node );
	return true;
}
bool DebugNodeContentWidget::updateLayout( ) {
	int maxWidth = this->width( );
	int maxHeiht = this->height( );
	int toolHeight = tool->height( );
	tool->setFixedWidth( maxWidth );
	outputItemScrollArea->move( 0, toolHeight );
	maxHeiht = maxHeiht - toolHeight;
	outputItemScrollArea->setFixedSize( maxWidth, maxHeiht );
	auto viewport = outputItemScrollArea->viewport( );
	maxWidth = viewport->width( );
	outPortItemScrollWidget->setMaximumWidth( maxWidth );
	return true;
}
void DebugNodeContentWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
