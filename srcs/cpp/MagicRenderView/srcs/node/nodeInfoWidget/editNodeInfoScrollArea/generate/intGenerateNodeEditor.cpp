#include "intGenerateNodeEditor.h"

#include <QVBoxLayout>

#include "../../../../director/varDirector.h"
#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "../../mainInfoWidget/nodeInfoWidget.h"
#include "generateItemWidget/generateItemWidget.h"
#include "titleTool/addGenerateTool.h"

void IntGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	size_t count = intGenerateItemWidgetVector.size( );
	auto widgetItemData = intGenerateItemWidgetVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		delete widgetItemData[ index ];
	intGenerateItemWidgetVector.clear( );
	bindGenerateVector = nullptr;
	parentVarDirector->release( newCreactePtr );
	newCreactePtr = nullptr;
}
bool IntGenerateNodeEditor::createJumpItem( NodeRefLinkInfo *node_ref_link_info ) {
	return false;
}
bool IntGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( newCreactePtr == nullptr )
		return false;
	size_t count = newCreactePtr->size( );
	size_t generateItemWidgetCount = intGenerateItemWidgetVector.size( );
	auto widgetItemData = intGenerateItemWidgetVector.data( );
	size_t index;
	if( count == 0 ) {
		if( generateItemWidgetCount != count ) {
			for( index = 0; index < generateItemWidgetCount; ++index )
				delete widgetItemData[ index ];
			intGenerateItemWidgetVector.clear( );
		}
		return true;
	}
	auto data = newCreactePtr->data( );
	if( generateItemWidgetCount != count ) {
		if( generateItemWidgetCount > count ) {
			for( index = count - 1; index < generateItemWidgetCount; ++index )
				delete widgetItemData[ index ];
		} else {
			intGenerateItemWidgetVector.resize( count );
			for( ; generateItemWidgetCount < count; ++generateItemWidgetCount )
				widgetItemData[ generateItemWidgetCount ] = new GenerateItemWidget( this );
			widgetItemData = intGenerateItemWidgetVector.data( );
		}
	}
	for( index = 0; index < count; ++index )
		widgetItemData[ index ]->setInfo( index, QString::number( data[ index ] ) );
	return true;
}
void IntGenerateNodeEditor::updateLayout( ) {

}
IntGenerateNodeEditor::IntGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	addGenerateTool = new AddGenerateTool( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	mainLayout->addWidget( addGenerateTool );
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
