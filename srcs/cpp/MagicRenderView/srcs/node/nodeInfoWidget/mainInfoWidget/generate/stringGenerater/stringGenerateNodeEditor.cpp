#include "stringGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "generRenderWidget/stringGenerateRenderScrollArea.h"
#include "generRenderWidget/stringGenerateRenderWidget.h"
#include "titleTool/stringGenerateTool.h"

void StringGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	stringGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool StringGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( stringGenerateVector == nullptr )
		return false;
	size_t count = stringGenerateVector->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = stringGenerateVector->data( );
		for( index = 0; index < count; ++index )
			generateRenderWidget->setInfo( index, data[ index ] );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	return true;
}
void StringGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void StringGenerateNodeEditor::addItem( StringGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void StringGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
StringGenerateNodeEditor::StringGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new StringGenerateTool( mainWidget );
	generateRenderScrollArea = new StringGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &StringGenerateTool::addItem_signal, [this] ( StringGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool StringGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void StringGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	stringGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto intArratPtr = stringGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		intArratPtr[ index ] = arrayPtr[ index ];
}
void StringGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void StringGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
