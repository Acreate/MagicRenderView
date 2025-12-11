#include "intGenerateNodeEditor.h"

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
	size_t count = intGenerateItemWidgetVector->size( );
	auto widgetItemData = intGenerateItemWidgetVector->data( );
	size_t index;
	for( index = 0; index < count; ++index )
		delete widgetItemData[ index ];
	intGenerateItemWidgetVector->clear( );
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
	size_t generateItemWidgetCount = intGenerateItemWidgetVector->size( );
	auto widgetItemData = intGenerateItemWidgetVector->data( );
	size_t index;
	if( count == 0 ) {
		if( generateItemWidgetCount != count ) {
			for( index = 0; index < generateItemWidgetCount; ++index )
				delete widgetItemData[ index ];
			intGenerateItemWidgetVector->clear( );
			generateRenderWidget->updateLayoutSort( );
		}
	} else {
		auto data = newCreactePtr->data( );
		if( generateItemWidgetCount != count ) {
			if( generateItemWidgetCount > count ) {
				for( index = count - 1; index < generateItemWidgetCount; ++index )
					delete widgetItemData[ index ];
			} else {
				intGenerateItemWidgetVector->resize( count );
				for( ; generateItemWidgetCount < count; ++generateItemWidgetCount )
					widgetItemData[ generateItemWidgetCount ] = new GenerateItemWidget( this );
				widgetItemData = intGenerateItemWidgetVector->data( );
			}
			generateRenderWidget->updateLayoutSort( );
		}
		for( index = 0; index < count; ++index )
			widgetItemData[ index ]->setInfo( index, QString::number( data[ index ] ) );
	}
	addGenerateTool->setMaxIndex( count + 1 );
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
void IntGenerateNodeEditor::addItem( AddGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant, const QString &var_value ) {
	bool result = false;
	qulonglong uLongLong = var_value.toULongLong( &result );
	if( result == false )
		return;
	
}
IntGenerateNodeEditor::IntGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new AddGenerateTool( mainWidget );
	generateRenderScrollArea = new GenerateRenderScrollArea( this );

	generateRenderWidget = generateRenderScrollArea->getViewWidget( );
	intGenerateItemWidgetVector = generateRenderWidget->getIntGenerateItemWidgetVector( );

	connect( addGenerateTool, &AddGenerateTool::addItem_signal, [this] ( AddGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant, const QString &var_value ) {
		this->addItem( signal_ptr, index, index_text, index_variant, var_value );
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
