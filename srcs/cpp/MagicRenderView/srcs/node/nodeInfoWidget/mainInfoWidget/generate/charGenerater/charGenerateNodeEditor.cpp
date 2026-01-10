#include "charGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "../intGenerater/intGenerateNodeEditor.h"
#include "generRenderWidget/charGenerateRenderScrollArea.h"
#include "generRenderWidget/charGenerateRenderWidget.h"
#include "titleTool/charGenerateTool.h"

void CharGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	charGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool CharGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( charGenerateVector == nullptr )
		return false;
	size_t count = charGenerateVector->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = charGenerateVector->data( );
		for( index = 0; index < count; ++index )
			generateRenderWidget->setInfo( index, data[ index ] );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	return true;
}
void CharGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void CharGenerateNodeEditor::addItem( CharGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void CharGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
CharGenerateNodeEditor::CharGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new CharGenerateTool( mainWidget );
	generateRenderScrollArea = new CharGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &CharGenerateTool::addItem_signal, [this] ( CharGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool CharGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void CharGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	charGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto charPtr = charGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ].length( ) > 0 )
			charPtr[ index ] = arrayPtr[ index ].data( )[ 0 ];
}
void CharGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void CharGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
