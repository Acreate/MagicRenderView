#include "jumpNodeEditor.h"

#include <QVBoxLayout>

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../node/node.h"
#include "../../mainInfoWidget/nodeInfoWidget.h"
#include "subWidget/jumpNodeWidgetItem.h"
void JumpNodeEditor::releaseResource( ) {
	size_t count = unionJumpNodeVector.size( );
	auto jumpNodeWidgetItemArrayPtr = unionJumpNodeVector.data( );
	for( size_t index = 0; index < count; ++index )
		delete jumpNodeWidgetItemArrayPtr[ index ];
	unionJumpNodeVector.clear( );
}
bool JumpNodeEditor::createJumpItem( Node *node_ref_link_info ) {

	return true;
}
JumpNodeEditor::JumpNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

}
bool JumpNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	
	return createJumpItem( init_node );
}
