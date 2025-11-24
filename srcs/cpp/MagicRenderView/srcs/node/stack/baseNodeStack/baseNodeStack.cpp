#include "baseNodeStack.h"

#include <QMenu>

#include "../../../app/application.h"

#include "../../../director/printerDirector.h"

#include "../../../widget/drawNodeWidget.h"
#include "../../../widget/mainWidget.h"

#include "../../../win/mainWindow.h"

#include "../../node/control/beginNode.h"
#include "../../node/control/endNode.h"
#include "../../node/control/jumpNode.h"
#include "../../node/control/pointNode.h"
#include "../../node/logic/ifNode.h"
#include "../../node/logic/whileNode.h"

#define emaplace_back_node( _Type) nodeGenerate.emplace_back( std::pair< QString, std::function< Node *( ) > >( _Type::nodeTypeName( ), [] { return new _Type( ); } ) )
bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );

	emaplace_back_node( BeginNode );
	emaplace_back_node( EndNode );
	emaplace_back_node( JumpNode );
	emaplace_back_node( PointNode );
	emaplace_back_node( IfNode );
	emaplace_back_node( WhileNode );

	mainMenu = new QMenu( name );

	size_t index;
	size_t count = nodeGenerate.size( );
	auto nodeArrayPtr = nodeGenerate.data( );
	for( index = 0; index < count; ++index )
		if( createMenuAtNodeType( nodeArrayPtr[ index ].first, nodeArrayPtr[ index ].second ) == false ) {
			QString msg( "[ %1 ]节点菜单对象初始化失败" );
			printerDirector->error( msg.arg( nodeArrayPtr[ index ].first ) );
			releaseMainMenu( );
			nodeGenerate.clear( );
			return false;
		}
	count = subMenus.size( );
	index = 0;
	auto subMenuArrayPtr = subMenus.data( );
	for( ; index < count; ++index )
		if( subMenuArrayPtr[ index ].first.size( ) == 1 )
			mainMenu->addMenu( subMenuArrayPtr[ index ].second );

	auto actionArrayPtr = actions.data( );
	count = actions.size( );
	index = 0;
	for( ; index < count; ++index )
		if( actionArrayPtr[ index ].first.size( ) == 1 )
			mainMenu->addAction( actionArrayPtr[ index ].second );
	return true;
}

BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
