#include "intGenerateNodeEditor.h"

#include <QMenu>
#include <QVBoxLayout>

#include "../../../../director/varDirector.h"
#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "../../mainInfoWidget/nodeInfoWidget.h"
#include "generateItemWidget/generateItemWidget.h"
#include "generRenderWidget/generateRenderScrollArea.h"
#include "generRenderWidget/generateRenderWidget.h"
#include "titleTool/addGenerateTool.h"

void IntGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	bindGenerateVector = nullptr;
	newCreactePtr->clear( );
	updateGenerateItemInfo( );
	parentVarDirector->release( newCreactePtr );
	newCreactePtr = nullptr;
}

bool IntGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( newCreactePtr == nullptr )
		return false;
	size_t count = newCreactePtr->size( );
	size_t index;
	generateRenderWidget->resize( count );
	if( count != 0 ) {
		auto data = newCreactePtr->data( );
		for( index = 0; index < count; ++index )
			generateRenderWidget->setInfo( index, QString::number( data[ index ] ) );
	}
	addGenerateTool->setMaxIndex( count + 1 );
	generateRenderWidget->updateLayoutSort( );
	return true;
}
void IntGenerateNodeEditor::updateLayout( ) {
	auto viewportSize = maximumViewportSize( );
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
	viewportSize = QSize( currentWidth, currentHeight - addGenerateToolHeight );
	generateRenderScrollArea->setFixedSize( viewportSize );
}
void IntGenerateNodeEditor::addItem( AddGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
	size_t count = newCreactePtr->size( );
	if( index < count )
		newCreactePtr->insert( newCreactePtr->begin( ) + index, 0 );
	else
		newCreactePtr->emplace_back( 0 );
	updateGenerateItemInfo( );
}
void IntGenerateNodeEditor::requesPopItemMenu( QMenu *pop_menu ) {
	pop_menu->show( );
}
IntGenerateNodeEditor::IntGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new AddGenerateTool( mainWidget );
	generateRenderScrollArea = new GenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );

	connect( addGenerateTool, &AddGenerateTool::addItem_signal, [this] ( AddGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant ) {
		this->addItem( signal_ptr, index, index_text, index_variant );
	} );
}
bool IntGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	if( bindGenerateVector == nullptr )
		return false;
	if( parentVarDirector->create( newCreactePtr ) == false )
		return false;
	resetGenerateVarVector( );
	return true;
}
void IntGenerateNodeEditor::resetGenerateVarVector( ) {
	*newCreactePtr = *bindGenerateVector;
	updateGenerateItemInfo( );
}
void IntGenerateNodeEditor::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	updateLayout( );
}
void IntGenerateNodeEditor::showEvent( QShowEvent *event ) {
	EditorNodeInfoScrollArea::showEvent( event );
	updateLayout( );
}
