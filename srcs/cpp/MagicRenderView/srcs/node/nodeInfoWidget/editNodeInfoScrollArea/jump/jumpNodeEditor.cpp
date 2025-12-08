#include "jumpNodeEditor.h"

#include <QVBoxLayout>

#include "../../../../app/application.h"
#include "../../../../director/nodeDirector.h"
#include "../../../../director/printerDirector.h"
#include "../../../../enums/widgetEnum.h"
#include "../../../../srack/srackInfo.h"
#include "../../../node/node.h"
#include "../../../nodeInfo/nodeBuilderTools.h"
#include "../../../nodeInfo/nodeRefLinkInfo.h"
#include "../../mainInfoWidget/nodeInfoWidget.h"
#include "subWidget/jumpNodeWidgetItem.h"
void JumpNodeEditor::showNodeInfoWidgetLeft( NodeRefLinkInfo *node_ref_link_info ) {
	auto nodeDirector = Application::getInstancePtr( )->getNodeDirector( );
	auto nodeInfoWidget = nodeDirector->getNodeWidgeInfo( node_ref_link_info->getCurrentNode( ) );
	if( nodeInfoWidget == nullptr )
		return;
	if( leftWidget == nodeInfoWidget )
		return;
	if( leftWidget )
		leftWidget->hide( );
	leftWidget = nodeInfoWidget;
	if( leftWidget == rightWidget )
		rightWidget->hide( );
	leftWidget->show( );
	leftWidget->installEventFilter( this );
	leftWidget->showNodeInfoWidget( WidgetEnum::ShowType::Left );
}
void JumpNodeEditor::showNodeInfoWidgetRight( NodeRefLinkInfo *node_ref_link_info ) {
	auto nodeDirector = Application::getInstancePtr( )->getNodeDirector( );
	auto nodeInfoWidget = nodeDirector->getNodeWidgeInfo( node_ref_link_info->getCurrentNode( ) );
	if( nodeInfoWidget == nullptr )
		return;
	if( rightWidget == nodeInfoWidget )
		return;
	if( rightWidget )
		rightWidget->hide( );
	rightWidget = nodeInfoWidget;
	if( leftWidget == rightWidget )
		leftWidget->hide( );
	rightWidget->show( );
	rightWidget->installEventFilter( this );
	rightWidget->showNodeInfoWidget( WidgetEnum::ShowType::Right );
}
void JumpNodeEditor::releaseResource( ) {
	size_t count = unionJumpNodeVector.size( );
	auto jumpNodeWidgetItemArrayPtr = unionJumpNodeVector.data( );
	for( size_t index = 0; index < count; ++index )
		delete jumpNodeWidgetItemArrayPtr[ index ];
	unionJumpNodeVector.clear( );
}
bool JumpNodeEditor::createJumpItem( NodeRefLinkInfo *node_ref_link_info ) {

	std::vector< std::vector< NodeRefLinkInfo * > > nodeRefLinkVector;
	if( NodeBuilderTools::JumpNodeBuilderTools::analysisJumpNodeRef( node_ref_link_info, nodeRefLinkVector ) == false )
		return false;
	size_t count = nodeRefLinkVector.size( );
	if( count == 0 )
		return false;
	auto nodeRefLinkInfosArrayPtr = nodeRefLinkVector.data( );
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
		createItem->setNodeRefVector( nodeRefLinkInfosArrayPtr[ index ] );
		mainLayout->addWidget( createItem );
		jumpNodeWidgetItemArrayPtr[ index ] = createItem;
	}
	return true;
}
void JumpNodeEditor::hideEvent( QHideEvent *event ) {
	EditorNodeInfoScrollArea::hideEvent( event );
	releaseResource( );
}
bool JumpNodeEditor::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {
	bool eventFilter = EditorNodeInfoScrollArea::eventFilter( event_obj_ptr, event_type );
	if( event_obj_ptr == leftWidget ) {
		switch( event_type->type( ) ) {
			case QEvent::Hide :
				leftWidget->removeEventFilter( this );
				leftWidget = nullptr;
				break;

		}
		return eventFilter;
	}
	if( event_obj_ptr == rightWidget ) {
		switch( event_type->type( ) ) {
			case QEvent::Hide :
				rightWidget->removeEventFilter( this );
				rightWidget = nullptr;
				break;

		}
		return eventFilter;
	}
	return eventFilter;
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
		std::vector< NodeRefLinkInfo * > jumpNodeVector;
		if( NodeBuilderTools::Point::findJumNodeRef( init_node->getNodeRefLinkInfoPtr( ), jumpNodeVector ) == false )
			return false;
		size_t count = jumpNodeVector.size( );
		auto arrayPtr = jumpNodeVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( createJumpItem( arrayPtr[ index ] ) == false ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "[%1]节点窗口模块创建异常" ).arg( arrayPtr[ index ]->getCurrentNode( )->getNodeName( ) ), Create_SrackInfo( ) );
				return false;
			}
		return true;
	}
	return createJumpItem( init_node->getNodeRefLinkInfoPtr( ) );
}
