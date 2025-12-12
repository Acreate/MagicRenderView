#include "drawHighlightWidget.h"

#include <QPainter>

#include "../node/node/node.h"
#include "mainWidget.h"
void DrawHighlightWidget::releaseNode( Node *release_node, const SrackInfo &srack_info ) {
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == release_node ) {
			drawNodeType.erase( drawNodeType.begin( ) + drawNodeTypeArratIndex );
			drawNodeTypeArratCount = drawNodeType.size( );
			drawNodeTypeArratPtr = drawNodeType.data( );
			break;
		}
}
DrawHighlightWidget::DrawHighlightWidget( MainWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	drawNodeTypeArratCount = 0;
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
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == set_node_ptr ) {
			drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first = new_node_type;
			update( );
			return;
		}
	drawNodeType.emplace_back( set_node_ptr, std::pair( new_node_type, [] ( Node *, NodeEnum::NodeStyleType ) { } ) );
	drawNodeTypeArratCount = drawNodeType.size( );
	drawNodeTypeArratPtr = drawNodeType.data( );
	connect( set_node_ptr, &Node::release_node_signal, this, &DrawHighlightWidget::releaseNode );
	update( );
}
void DrawHighlightWidget::setNodeDrawNodeType( Node *set_node_ptr, NodeEnum::NodeStyleType new_node_type, const std::function< void( Node *, NodeEnum::NodeStyleType ) > &paint_event ) {
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		if( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first == set_node_ptr ) {
			drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first = new_node_type;
			drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.second = paint_event;
			update( );
			return;
		}
	drawNodeType.emplace_back( set_node_ptr, std::pair( new_node_type, paint_event ) );
	drawNodeTypeArratCount = drawNodeType.size( );
	drawNodeTypeArratPtr = drawNodeType.data( );
	connect( set_node_ptr, &Node::release_node_signal, this, &DrawHighlightWidget::releaseNode );
	update( );
}
DrawHighlightWidget::~DrawHighlightWidget( ) {
	emit release_signal( this );
}
void DrawHighlightWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	if( drawNodeTypeArratCount == 0 )
		return;
	QPainter painter( this );
	QPen normalPen;
	QPen createPen;
	QPen selectPen;
	normalPen.setWidth( 5 );
	normalPen.setColor( Qt::GlobalColor::black );
	createPen.setWidth( 5 );
	createPen.setColor( Qt::GlobalColor::green );
	selectPen.setWidth( 5 );
	selectPen.setColor( Qt::GlobalColor::yellow );
	for( drawNodeTypeArratIndex = 0; drawNodeTypeArratIndex < drawNodeTypeArratCount; ++drawNodeTypeArratIndex )
		switch( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].second.first ) {
			case NodeEnum::NodeStyleType::None :
				painter.setPen( normalPen );
				painter.drawRect( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first->geometry( ) );
				break;
			case NodeEnum::NodeStyleType::Call_Function :
				break;
			case NodeEnum::NodeStyleType::Create :
				painter.setPen( createPen );
				painter.drawRect( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first->geometry( ) );
				break;
			case NodeEnum::NodeStyleType::Select_Active :
				painter.setPen( selectPen );
				painter.drawRect( drawNodeTypeArratPtr[ drawNodeTypeArratIndex ].first->geometry( ) );
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

}
bool DrawHighlightWidget::init( MainWidget *parent ) {
	setParent( parent );
	drawNodeType.clear( );
	drawNodeTypeArratCount = 0;
	drawNodeTypeArratPtr = nullptr;
	return true;
}
