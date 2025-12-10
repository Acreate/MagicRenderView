#include "intGenerateNodeEditor.h"

#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "generateItemWidget/generateItemWidget.h"

void IntGenerateNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	size_t generateItemWidgetCount = intGenerateItemWidgetVector.size( );
	auto widgetItemData = intGenerateItemWidgetVector.data( );
	size_t index;
	for( index = 0; index < generateItemWidgetCount; ++index )
		delete widgetItemData[ index ];
	intGenerateItemWidgetVector.clear( );
	bindGenerateVector = nullptr;
}
bool IntGenerateNodeEditor::createJumpItem( NodeRefLinkInfo *node_ref_link_info ) {
	return false;
}
bool IntGenerateNodeEditor::updateGenerateItemInfo( ) {
	if( bindGenerateVector == nullptr )
		return false;
	size_t count = bindGenerateVector->size( );
	size_t generateItemWidgetCount = intGenerateItemWidgetVector.size( );
	auto widgetItemData = intGenerateItemWidgetVector.data( );
	size_t index;
	if( count == 0 ) {
		if( generateItemWidgetCount != count )
			for( index = 0; index < generateItemWidgetCount; ++index )
				delete widgetItemData[ index ];
		intGenerateItemWidgetVector.clear( );
	}
	auto data = bindGenerateVector->data( );
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
IntGenerateNodeEditor::IntGenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
}
bool IntGenerateNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	updateGenerateItemInfo( );
	return true;
}
