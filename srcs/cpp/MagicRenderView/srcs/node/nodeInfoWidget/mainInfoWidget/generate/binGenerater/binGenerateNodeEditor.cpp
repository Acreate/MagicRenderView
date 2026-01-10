#include "binGenerateNodeEditor.h"


#include <QMenu>
#include <QVBoxLayout>

#include "generRenderWidget/binGenerateRenderScrollArea.h"
#include "generRenderWidget/binGenerateRenderWidget.h"
#include "titleTool/binGenerateTool.h"

void BinGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	bindGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool BinGenerateNodeEditor::updateGenerateItemInfo( ) {
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
void BinGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void BinGenerateNodeEditor::addItem( BinGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void BinGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
BinGenerateNodeEditor::BinGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new BinGenerateTool( mainWidget );
	generateRenderScrollArea = new BinGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &BinGenerateTool::addItem_signal, [this] ( BinGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool BinGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void BinGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	bindGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto intArratPtr = bindGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		intArratPtr[ index ] = arrayPtr[ index ].toULongLong( );
}
void BinGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void BinGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
