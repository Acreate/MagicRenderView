#include "drawHighlightWidget.h"

#include <QPainter>

#include "../node/node/node.h"
#include "mainWidget.h"
void DrawHighlightWidget::releaseNode( Node *release_node, const SrackInfo &srack_info ) {
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == release_node ) {
			createNodePairPtr = nullptr;
			selectNodePairPtr = nullptr;
			drawNodeType.erase( drawNodeType.begin( ) + drawNodeTypeArratIndex );
			drawNodeTypeArratCount = drawNodeType.size( );
			drawNodeTypeArratPtr = drawNodeType.data( );
			break;
		}
}
void DrawHighlightWidget::setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type, const TPaintCallFunction &paint_event, const bool set_function ) {
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == set_node_ptr ) {
			drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first = new_node_type;
			if( set_function )
				drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.second = paint_event;
			switch( new_node_type ) {
				case NodeEnum::NodeStyleType::None :
					break;
				case NodeEnum::NodeStyleType::Call_Function :
					break;
				case NodeEnum::NodeStyleType::Create :

					break;
				case NodeEnum::NodeStyleType::Select_Active :
					if( selectNodePairPtr )
						selectNodePairPtr->second.first = NodeEnum::NodeStyleType::None;
					selectNodePairPtr = drawNodeTypeArratPtr + drawNodeTypeArratIndex;
					if( createNodePairPtr )
						createNodePairPtr->second.first = NodeEnum::NodeStyleType::None;
					createNodePairPtr = drawNodeTypeArratIndex + drawNodeTypeArratPtr;
					break;
				case NodeEnum::NodeStyleType::Select_Old :
					break;
				case NodeEnum::NodeStyleType::Warning :
					break;
				case NodeEnum::NodeStyleType::Error :
					break;
				case NodeEnum::NodeStyleType::Advise :
					break;
			}
			update( );
			return;
		}
	if( selectNodePairPtr )
		selectNodePairPtr->second.first = NodeEnum::NodeStyleType::None;
	selectNodePairPtr = nullptr;
	if( createNodePairPtr )
		createNodePairPtr->second.first = NodeEnum::NodeStyleType::None;
	drawNodeType.emplace_back( set_node_ptr, std::pair( new_node_type, paint_event ) );
	drawNodeTypeArratCount = drawNodeType.size( );
	drawNodeTypeArratPtr = drawNodeType.data( );
	createNodePairPtr = drawNodeTypeArratCount - 1 + drawNodeTypeArratPtr;

	connect( set_node_ptr, &Node::release_node_signal, this, &DrawHighlightWidget::releaseNode );
	update( );
}
DrawHighlightWidget::DrawHighlightWidget( MainWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	drawNodeTypeArratCount = 0;
	createNodePairPtr = 0;
	selectNodePairPtr = 0;
	drawNodeTypeArratPtr = nullptr;
}
NodeEnum::NodeStyleType DrawHighlightWidget::getNodeDrawNodeType( const Node *find_node_ptr ) const {
	for( auto drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == find_node_ptr )
			return drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first;
	return NodeEnum::NodeStyleType::None;
}
DrawHighlightWidget::TPaintCallFunction DrawHighlightWidget::getNodeDrawNodeCallFuntionType( const Node *find_node_ptr ) const {
	for( auto drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == find_node_ptr )
			return drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.second;
	return nullptr;
}
DrawHighlightWidget::TPairType DrawHighlightWidget::getNodeDrawNodePairType( const Node *find_node_ptr ) const {
	for( auto drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == find_node_ptr )
			return drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second;
	return TPairType { NodeEnum::NodeStyleType::None, nullptr };
}
void DrawHighlightWidget::setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type ) {
	setNodeDrawNodeType( set_node_ptr, new_node_type, nullptr, false );
}
void DrawHighlightWidget::setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type, const std::function< void( Node *, NodeEnum::NodeStyleType ) > &paint_event ) {

	setNodeDrawNodeType( set_node_ptr, new_node_type, nullptr, true );
}
DrawHighlightWidget::~DrawHighlightWidget( ) {
	emit release_signal( this );
}
void DrawHighlightWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	if( drawNodeTypeArratCount == 0 )
		return;
	QPainter painter( this );
	QPen normalPen = painter.pen( );
	normalPen.setWidth( 5 );
	normalPen.setColor( Qt::GlobalColor::black );
	painter.setPen( normalPen );
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		switch( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first ) {
			case NodeEnum::NodeStyleType::None :
				painter.drawRect( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first->geometry( ) );
				break;
			case NodeEnum::NodeStyleType::Call_Function :
				break;
			case NodeEnum::NodeStyleType::Create :
				break;
			case NodeEnum::NodeStyleType::Select_Active :
				break;
			case NodeEnum::NodeStyleType::Select_Old :
				break;
			case NodeEnum::NodeStyleType::Warning :
				break;
			case NodeEnum::NodeStyleType::Error :
				break;
			case NodeEnum::NodeStyleType::Advise :
				break;
		}
	if( selectNodePairPtr ) {
		normalPen.setWidth( 5 );
		normalPen.setColor( Qt::GlobalColor::yellow );
		painter.setPen( normalPen );
		painter.drawRect( selectNodePairPtr->first->geometry( ) );
	}
	if( createNodePairPtr ) {
		normalPen.setWidth( 5 );
		normalPen.setColor( Qt::GlobalColor::green );
		painter.setPen( normalPen );
		painter.drawRect( createNodePairPtr->first->geometry( ) );
	}
}
bool DrawHighlightWidget::init( MainWidget *parent ) {
	setParent( parent );
	drawNodeType.clear( );
	drawNodeTypeArratCount = 0;
	drawNodeTypeArratPtr = nullptr;
	createNodePairPtr = nullptr;
	selectNodePairPtr = nullptr;
	return true;
}
