#include "uIntGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "../intGenerater/intGenerateNodeEditor.h"
#include "generRenderWidget/uIntGenerateRenderScrollArea.h"
#include "generRenderWidget/uIntGenerateRenderWidget.h"
#include "titleTool/uIntGenerateTool.h"

void UIntGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	bindGenerateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool UIntGenerateNodeEditor::updateGenerateItemInfo( ) {
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
void UIntGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void UIntGenerateNodeEditor::addItem( UIntGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void UIntGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
UIntGenerateNodeEditor::UIntGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new UIntGenerateTool( mainWidget );
	generateRenderScrollArea = new UIntGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &UIntGenerateTool::addItem_signal, [this] ( UIntGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool UIntGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void UIntGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	bindGenerateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto intArratPtr = bindGenerateVector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		intArratPtr[ index ] = arrayPtr[ index ].toULongLong( );
}
void UIntGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void UIntGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
