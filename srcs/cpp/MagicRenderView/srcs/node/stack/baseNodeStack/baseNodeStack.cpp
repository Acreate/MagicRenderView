#include "baseNodeStack.h"

#include "../../node/control/beginNode.h"
#include "../../node/control/endNode.h"
#include "../../node/control/jumpNode.h"
#include "../../node/control/pointNode.h"
#include "../../node/logic/ifNode.h"
#include "../../node/logic/whileNode.h"

#define emaplace_back_node( _Type ) nodeGenerate.emplace_back( std::pair< QString, std::function< Node *( ) > >( _Type::nodeTypeName( ), [] { return new _Type( ); } ) )
bool BaseNodeStack::init( ) {
	setObjectName( tr( "基础节点" ) );
	emaplace_back_node( BeginNode );
	emaplace_back_node( EndNode );
	emaplace_back_node( JumpNode );
	emaplace_back_node( PointNode );
	emaplace_back_node( IfNode );
	emaplace_back_node( WhileNode );
	using IteratorType = std::pair< QString, std::function< Node *( ) > >;
	std::ranges::sort( nodeGenerate, [] ( const IteratorType &left, const IteratorType &right ) {
		return left.first > right.first;
	} );

	return true;
}
QMenu * BaseNodeStack::toMenu( ) {
	return nullptr;
}
BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
