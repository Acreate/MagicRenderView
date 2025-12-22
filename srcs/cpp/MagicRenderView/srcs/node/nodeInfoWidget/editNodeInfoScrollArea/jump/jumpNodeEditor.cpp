#include "jumpNodeEditor.h"

#include <QVBoxLayout>

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../node/node.h"
#include "../../../nodeInfo/nodeBuilderTools.h"
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

	std::vector< std::vector< Node * > > nodeRefLinkVector;
	if( NodeBuilderTools::JumpNodeBuilderTools::analysisJumpNodeRef( node_ref_link_info, nodeRefLinkVector ) == false )
		return false;
	size_t count = nodeRefLinkVector.size( );
	if( count == 0 )
		return false;
	auto NodesArrayPtr = nodeRefLinkVector.data( );
	size_t index = 0;
	unionJumpNodeVector.resize( count );
	auto jumpNodeWidgetItemArrayPtr = unionJumpNodeVector.data( );
	for( ; index < count; ++index ) {
		auto createItem = new JumpNodeWidgetItem( mainWidget );
		auto itemPen = createItem->getItemPen( );
		itemPen.setColor( QColor( 0, 128, 0 ) );
		itemPen.setWidth( 4 );
		createItem->setItemPen( itemPen );
		itemPen = createItem->getSubItemPen( );
		itemPen.setColor( QColor( 255, 69, 0 ) );
		itemPen.setWidth( 4 );
		createItem->setSubItemPen( itemPen );

		connect( createItem, &JumpNodeWidgetItem::showNodeInfoWidgetLeft, this, &JumpNodeEditor::showNodeInfoWidgetLeft );
		connect( createItem, &JumpNodeWidgetItem::showNodeInfoWidgetRight, this, &JumpNodeEditor::showNodeInfoWidgetRight );
		createItem->setIsPopMenu( true );
		createItem->setNodeRefVector( NodesArrayPtr[ index ] );
		mainLayout->addWidget( createItem );
		jumpNodeWidgetItemArrayPtr[ index ] = createItem;
	}
	return true;
}
JumpNodeEditor::JumpNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	leftWidget = nullptr;
	rightWidget = nullptr;
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

}
bool JumpNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	if( init_node->getNodeType( ) == NodeEnum::NodeType::Point ) {
		std::vector< Node * > jumpNodeVector;
		if( NodeBuilderTools::Point::findJumNodeRef( init_node, jumpNodeVector ) == false )
			return false;
		size_t count = jumpNodeVector.size( );
		auto arrayPtr = jumpNodeVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( createJumpItem( arrayPtr[ index ] ) == false ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "[%1]节点窗口模块创建异常" ).arg( arrayPtr[ index ]->getNodeName( ) ), Create_SrackInfo( ) );
				return false;
			}
		return true;
	}
	return createJumpItem( init_node );
}
