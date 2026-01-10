
#include "floatGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "generRenderWidget/floatGenerateRenderScrollArea.h"
#include "generRenderWidget/floatGenerateRenderWidget.h"
#include "titleTool/floatGenerateTool.h"

void FloatGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	bindGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool FloatGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( bindGenerateVector == nullptr )
		return false;
	size_t count = bindGenerateVector->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = bindGenerateVector->data( );
		for( index = 0; index < count; ++index )
			generateRenderWidget->setInfo( index, QString::number( data[ index ] ) );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	return true;
}
void FloatGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void FloatGenerateNodeEditor::addItem( FloatGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getFloatGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void FloatGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
FloatGenerateNodeEditor::FloatGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new FloatGenerateTool( mainWidget );
	generateRenderScrollArea = new FloatGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &FloatGenerateTool::addItem_signal, [this] ( FloatGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool FloatGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void FloatGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	bindGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto intArratPtr = bindGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		intArratPtr[ index ] = arrayPtr[ index ].toDouble( );
}
void FloatGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void FloatGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
