#include "imageGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include <tools/imageTools.h>
#include "generRenderWidget/imageGenerateRenderScrollArea.h"
#include "generRenderWidget/imageGenerateRenderWidget.h"
#include "titleTool/imageGenerateTool.h"

void ImageGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	generateVector = nullptr;
	generateRenderWidget->resize( 0 );
}

bool ImageGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( generateVector == nullptr )
		return false;
	size_t count = generateVector->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = generateVector->data( );
		QString base64;
		for( index = 0; index < count; ++index )
			if( ImageTools::imageToBase64( data[ index ], base64 ) )
				generateRenderWidget->setInfo( index, base64 );
			else
				generateRenderWidget->setInfo( index, "error::转换异常!" );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	return true;
}
void ImageGenerateNodeEditor::updateEditorNodeInfoLayout( ) {
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
void ImageGenerateNodeEditor::addItem( ImageGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	generateRenderWidget->createItem( index );
	addGenerateTool->setMaxIndex( generateRenderWidget->getIntGenerateItemWidgetArratCount( ) + 1 );
	generateRenderWidget->updateVectorIndex( );
}
void ImageGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
ImageGenerateNodeEditor::ImageGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new ImageGenerateTool( mainWidget );
	generateRenderScrollArea = new ImageGenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &ImageGenerateTool::addItem_signal, [this] ( ImageGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool ImageGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}

void ImageGenerateNodeEditor::syncVarVector( ) {
	auto converTextVector = generateRenderWidget->converTextVector( );
	size_t count = converTextVector.size( );
	generateVector->resize( count );
	auto arrayPtr = converTextVector.data( );
	auto charPtr = generateVector->data( );
	size_t index = 0;
	QImage resultIame;
	for( ; index < count; ++index )
		if( arrayPtr[ index ].length( ) > 0 )
			if( ImageTools::base64ToImage( arrayPtr[ index ], resultIame ) )
				charPtr[ index ] = resultIame;
}
void ImageGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateEditorNodeInfoLayout( );
}
void ImageGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	//updateEditorNodeInfoLayout( );
}
