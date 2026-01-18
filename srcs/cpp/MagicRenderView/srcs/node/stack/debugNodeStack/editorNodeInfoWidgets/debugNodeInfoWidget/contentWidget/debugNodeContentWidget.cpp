#include "debugNodeContentWidget.h"

#include <node/node/node.h>
#include <qlayout.h>

#include "../../../debugNodes/outInfo/debugInfoNode.h"
#include "outPortItemScorllArea/outPortItemScorllArea.h"
#include "outPortItemScorllArea/outPortItemScorllWidget.h"
#include "toolWidget/debugNodeConetentToolsWidget.h"

DebugNodeContentWidget::DebugNodeContentWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	//QVBoxLayout *mainLayout = new QVBoxLayout( this );
	tool = new DebugNodeConetentToolsWidget( this );
	tool->move( 0, 0 );
	outputItemScorllArea = new OutPortItemScorllArea( this );
	outPortItemScorllWidget = outputItemScorllArea->getOutPortItemScorllWidget( );
	connect( tool, &DebugNodeConetentToolsWidget::click_builder_target_signal, this, &DebugNodeContentWidget::click_builder_target_signal );
	/*mainLayout->addWidget( tool, 0, Qt::AlignmentFlag::AlignTop );
	mainLayout->addWidget( outputItemScorllArea, 0 );*/
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
	outputItemScorllArea->move( 0, toolHeight );
	maxHeiht = maxHeiht - toolHeight;
	outputItemScorllArea->setFixedSize( maxWidth, maxHeiht );
	return true;
}
bool DebugNodeContentWidget::appendOutputPort( OutputPort *output_port_ptr, const QString &msg ) {
	return outPortItemScorllWidget->appendOutputItem( output_port_ptr, msg );
}
bool DebugNodeContentWidget::clear( ) {
	return outPortItemScorllWidget->clear( );;
}
void DebugNodeContentWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
	auto viewport = outputItemScorllArea->viewport( );
	int maxWidth = viewport->width( );
	outPortItemScorllWidget->setMaximumWidth( maxWidth );
}
