#include "drawNodeWidget.h"

#include "../app/application.h"

#include "../node/node/node.h"

void DrawNodeWidget::appendVector( Node *append_node ) {
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == nullptr ) {
				nodeArrayPtr[ index ] = append_node;
				return;
			}
	}
	nodeVector.emplace_back( append_node );
}
void DrawNodeWidget::removeVector( Node *remove_node ) {
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == remove_node ) {
				++index;
				for( ; index < count; ++index )
					if( nodeArrayPtr[ index ] == nullptr )
						break;
					else
						nodeArrayPtr[ index - 1 ] = nodeArrayPtr[ index ];
				nodeArrayPtr[ index - 1 ] = nullptr;
				return;
			}
	}
}
void DrawNodeWidget::raiseNode( Node *raise_node ) {
	size_t count = nodeVector.size( );
	if( count > 1 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		if( nodeArrayPtr[ index ] == nullptr ) // 整个列表为空，则退出
			return;
		size_t lastNode = count - 1;
		for( ; index < lastNode; --lastNode )
			if( nodeArrayPtr[ lastNode ] != nullptr )
				break; // 匹配最后一个有效节点
		if( nodeArrayPtr[ lastNode ] == raise_node ) // 末尾就是该节点，则退出
			return;
		index += 1; // 从 1 开始测试
		for( ; index < lastNode; ++index )
			if( nodeArrayPtr[ index ] == raise_node ) {
				// 元素往前推
				count = index + 1;
				for( ; count < lastNode; ++count )
					nodeArrayPtr[ count - 1 ] = nodeArrayPtr[ count ];
				nodeArrayPtr[ lastNode ] = raise_node; // 替换最后一个有效节点
				return;
			}
	}
}

DrawNodeWidget::DrawNodeWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
}
DrawNodeWidget::~DrawNodeWidget( ) {
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto buff = nodeVector;
		nodeVector.clear( );
		auto nodeArrayPtr = buff.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == nullptr )
				break;
			else
				delete nodeArrayPtr[ index ];
	}
}
bool DrawNodeWidget::addNode( Node *add_node, NodeRefLinkInfo *node_ref_link_info ) {
	if( add_node->init( this, node_ref_link_info ) == false )
		return false;
	QPoint fromGlobal = mapFromGlobal( menuPopPoint );
	if( fromGlobal.x( ) < 0 )
		fromGlobal.setX( 0 );
	if( fromGlobal.y( ) < 0 )
		fromGlobal.setY( 0 );
	add_node->move( fromGlobal );
	appendVector( add_node );
	connect( add_node, &Node::release_node_signal, this, &DrawNodeWidget::removeVector );
	return true;
}
bool DrawNodeWidget::getPointNodeClickInfo( const QPoint &click_point, NodeClickInfo &result_node_click_info ) {
	size_t count = nodeVector.size( );
	if( count == 0 )
		return false;
	size_t index = 0;
	auto nodeArrayPtr = nodeVector.data( );
	for( ; index < count; ++index )
		if( nodeArrayPtr[ index ] == nullptr )
			return false;
		else if( nodeArrayPtr[ index ]->geometry( ).contains( click_point ) == true ) {
			auto mapFromParent = nodeArrayPtr[ index ]->mapFromParent( click_point );
			if( nodeArrayPtr[ index ]->getPointInfo( mapFromParent, result_node_click_info ) == false )
				return false;
			return true;
		}
	return false;
}
