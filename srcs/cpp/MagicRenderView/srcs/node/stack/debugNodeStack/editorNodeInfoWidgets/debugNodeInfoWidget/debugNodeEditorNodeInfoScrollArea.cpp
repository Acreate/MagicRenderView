#include "debugNodeEditorNodeInfoScrollArea.h"

#include <app/application.h>
#include <node/stack/debugNodeStack/debugNodes/outInfo/debugInfoNode.h>
#include <win/mainWindow.h>

#include "contentWidget/debugNodeContentWidget.h"
void DebugNodeEditorNodeInfoScrollArea::runToNode_Slot( Node *run_target ) {
	Application *instancePtr = Application::getInstancePtr( );
	MainWindow *mainWindow = instancePtr->getMainWindow( );
	mainWindow->runToNode( run_target );
}
DebugNodeEditorNodeInfoScrollArea::DebugNodeEditorNodeInfoScrollArea( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	debugNodeContentWidget = new DebugNodeContentWidget( this );
	setWidget( debugNodeContentWidget );
	connect( debugNodeContentWidget, &DebugNodeContentWidget::click_builder_target_signal, this, &DebugNodeEditorNodeInfoScrollArea::runToNode_Slot );
	setWidgetResizable( false );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}
bool DebugNodeEditorNodeInfoScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	if( debugNodeContentWidget == nullptr || debugNodeContentWidget->init( ( DebugInfoNode * ) init_node ) == false )
		return false;
	return true;
}
void DebugNodeEditorNodeInfoScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
void DebugNodeEditorNodeInfoScrollArea::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	auto viewport = this->viewport( );
	auto viewSize = viewport->size( );
	debugNodeContentWidget->setFixedSize( viewSize );
}
