#include "generateNodeEditor.h"

#include <QScrollBar>
#include <QVBoxLayout>

#include "../../../node/node.h"
#include "panelWidget/generateInfoEditorTitle.h"
#include "panelWidget/generatePanelWidget.h"
GenerateNodeEditor::GenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {

	QWidget *mainWidget = new QWidget( this );
	setWidget( mainWidget );
	topAddVarMenu = new GenerateInfoEditorTitle( mainWidget );
	auto lambda = [] ( const QString &type_name, const QString &var_name ) {
		return nullptr;
	};
	addShowItemWidget = new GeneratePanelWidget(
		lambda,
		mainWidget );
	topAddVarMenu->move( 0, 0 );
}
bool GenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;

	QString newVarTypeName = init_node->getGenerateTypeName( );
	topAddVarMenu->setVarTypeName( newVarTypeName );
	topAddVarMenu->clearVarName( );
	return true;
}
void GenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	auto viewportSize = maximumViewportSize( );
	int width = viewportSize.width( );
	topAddVarMenu->setFixedWidth( width );
	int height = topAddVarMenu->height( );
	addShowItemWidget->move( 0, height );
	height = viewportSize.height( ) - height;
	if( height < 0 )
		height = 0;
	addShowItemWidget->setFixedSize( width, height );
}
