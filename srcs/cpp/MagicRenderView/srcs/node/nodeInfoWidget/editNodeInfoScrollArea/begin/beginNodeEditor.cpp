#include "beginNodeEditor.h"

#include <QVBoxLayout>
#include <qcoreevent.h>

#include "../../../../app/application.h"

#include "../../../../director/nodeDirector.h"

#include "../../../node/node.h"

#include "../../../nodeInfo/nodeBuilderTools.h"

#include "../../mainInfoWidget/nodeInfoWidget.h"

#include "subWidget/beginNodeItem.h"

BeginNodeEditor::BeginNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	leftWidget = nullptr;
	rightWidget = nullptr;
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	beginItem = new BeginNodeItem( mainWidget );
	mainLayout->addWidget( beginItem );
	processItem = new BeginNodeItem( mainWidget );
	mainLayout->addWidget( processItem );
	endItem = new BeginNodeItem( mainWidget );
	mainLayout->addWidget( endItem );

	auto itemPen = beginItem->getItemPen( );
	itemPen.setColor( QColor( 0, 128, 0 ) );
	itemPen.setWidth( 4 );
	beginItem->setItemPen( itemPen );
	itemPen = beginItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	beginItem->setSubItemPen( itemPen );

	itemPen = processItem->getItemPen( );
	itemPen.setColor( QColor( 255, 165, 0 ) );
	itemPen.setWidth( 4 );
	processItem->setItemPen( itemPen );
	itemPen = processItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	processItem->setSubItemPen( itemPen );

	itemPen = endItem->getItemPen( );
	itemPen.setColor( QColor( 30, 144, 255 ) );
	itemPen.setWidth( 4 );
	endItem->setItemPen( itemPen );
	itemPen = endItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	endItem->setSubItemPen( itemPen );

	connect( processItem, &BeginNodeItem::showNodeInfoWidgetLeft, this, &BeginNodeEditor::showNodeInfoWidgetLeft );
	connect( processItem, &BeginNodeItem::showNodeInfoWidgetRight, this, &BeginNodeEditor::showNodeInfoWidgetRight );

	beginItem->setIsPopMenu( false );
	endItem->setIsPopMenu( false );
}

BeginNodeEditor::~BeginNodeEditor( ) {

}
bool BeginNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;

	beginNodeRefLinkInfo = init_node;
	if( init_node->getNodeType( ) == NodeEnum::NodeType::End )
		if( NodeBuilderTools::BeginNodeBuilderTools::findRefBeginNode( beginNodeRefLinkInfo, beginNodeRefLinkInfo ) == false )
			return false;
	std::vector< Node * > resultNodeRefLinkVector;
	if( NodeBuilderTools::analysisNodeRef( beginNodeRefLinkInfo, resultNodeRefLinkVector ) == false )
		return false;
	size_t count = resultNodeRefLinkVector.size( );
	auto nodeRefLinkInfoArrayPtr = resultNodeRefLinkVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		switch( nodeRefLinkInfoArrayPtr[ index ]->getNodeType( ) ) {
			case NodeEnum::NodeType::Begin :
				beginNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
			case NodeEnum::NodeType::End :
				endNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
			default :
				processNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
		}
	if( NodeBuilderTools::sortProcessNodeRefArray( processNodeRefLinkVector.data( ), processNodeRefLinkVector.size( ) ) == false )
		return false; // 缺少依赖
	beginItem->setNodeRefVector( beginNodeRefLinkVector );

	processItem->setNodeRefVector( processNodeRefLinkVector );
	endItem->setNodeRefVector( endNodeRefLinkVector );
	return true;
}
void BeginNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	beginNodeRefLinkVector.clear( );
	processNodeRefLinkVector.clear( );
	endNodeRefLinkVector.clear( );
	beginNodeRefLinkInfo = nullptr;
}
