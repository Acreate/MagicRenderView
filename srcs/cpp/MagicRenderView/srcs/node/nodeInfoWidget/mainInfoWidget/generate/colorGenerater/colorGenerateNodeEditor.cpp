#include "colorGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "../../../../../tools/infoTool.h"
#include "../intGenerater/intGenerateNodeEditor.h"
#include "generRenderWidget/colorGenerateRenderScrollArea.h"
#include "generRenderWidget/colorGenerateRenderWidget.h"
#include "titleTool/colorGenerateTool.h"
void ColorGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	colorGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool ColorGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( colorGenerateVector == nullptr )
		return false;
	size_t count = colorGenerateVector->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = colorGenerateVector->data( );
		QString resultStr;
		for( index = 0; index < count; ++index )
			if( infoTool::toString( data[ index ], resultStr ) )
				generateRenderWidget->setInfo( index, resultStr );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	return true;
}
void ColorGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
	QWidget *widget = viewport( );
	if( widget == nullptr )
		return;
	auto viewportSize = widget->size( );
	int currentWidth = viewportSize.width( );
	if( currentWidth < 1 )
		return;
	int currentHeight = viewportSize.height( );
	if( currentHeight < 1 )
		return;
	addGenerateTool->move( 0, 0 );
	addGenerateTool->setFixedWidth( currentWidth );
	int addGenerateToolHeight = addGenerateTool->height( );
	generateRenderScrollArea->move( 0, addGenerateToolHeight );
	currentHeight -= addGenerateToolHeight;
	if( currentHeight < 1 )
		currentHeight = 0;
	viewportSize = QSize( currentWidth, currentHeight );
	generateRenderScrollArea->setFixedSize( viewportSize );
	generateRenderWidget->updateLayoutSort( );
}
void ColorGenerateNodeEditor::addItem( ColorGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void ColorGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
ColorGenerateNodeEditor::ColorGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new ColorGenerateTool( mainWidget );
	generateRenderScrollArea = new ColorGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &ColorGenerateTool::addItem_signal, [this] ( ColorGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool ColorGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void ColorGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	colorGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto charPtr = colorGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ].length( ) > 0 )
			charPtr[ index ] = QColor( arrayPtr[ index ] );
}
void ColorGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void ColorGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
