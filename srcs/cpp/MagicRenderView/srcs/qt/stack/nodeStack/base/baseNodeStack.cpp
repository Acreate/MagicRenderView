#include "./baseNodeStack.h"

#include "../../../menu/nodeAddMenu.h"

#include "qt/node/nodeWidget/base/nodeFileInfo.h"

#define emplace_back_NodeGenerate( type_, parent_, window_flags_, first_name_, ... ) \
	do{\
		nodeGenerate->emplace_back( std_pairt( first_name_, std_vector< QString >({ NodeFileInfo::staticMetaObject.className(  ),__VA_ARGS__ } ) ), [get_stack_function](  )->INodeWidget * {\
			type_ *nodeWidgetPtr = new type_(get_stack_function,{first_name_}, parent_, window_flags_);\
			return nodeWidgetPtr;\
			}\
		);\
	}while(false)

#define emplace_back_NodeGenerate_appendList( type_, parent_, window_flags_, first_name_, list_, ... ) \
	do{\
		auto nameList= std_vector< QString >({ NodeFileInfo::staticMetaObject.className(  ),__VA_ARGS__ } );\
		nameList.assign(list_.begin(), list_.end()); \
		nodeGenerate->emplace_back( std_pairt( first_name_,nameList  ), [get_stack_function,nameList](  )->INodeWidget * {\
			type_ *nodeWidgetPtr = new type_(get_stack_function,nameList, parent_, window_flags_);\
			return nodeWidgetPtr;\
	} )}while(false)
#define Type_to_QString( type_ ) QString( #type_)
BaseNodeStack::BaseNodeStack( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function ) : INodeStack( get_stack_function ), nodeGenerate( new std_vector< generateNodePairt > ) {
	stackTypeNames.clear( );
	stackTypeNames.emplace_back( "基础节点" );
	setObjectName( BaseNodeStack::staticMetaObject.className( ) );
	emplace_back_NodeGenerate( NodeFileInfo, nullptr, Qt::WindowFlags(), "文件信息" );
	menu->initMenu( this );
}
INodeWidget * BaseNodeStack::_newNode( const QString &type_name ) const {
	size_t count = nodeGenerate->size( );
	if( count == 0 )
		return nullptr;
	auto data = nodeGenerate->data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first.first == type_name )
			return data[ index ].second( );
		else
			for( auto &key : data[ index ].first.second )
				if( key == type_name )
					return data[ index ].second( );
	return nullptr;
}
INodeWidget * BaseNodeStack::generateNode( const QString &type_name, QWidget *parnet ) const {
	INodeWidget *newNode = _newNode( type_name );
	if( newNode )
		newNode->setParent( parnet );
	return newNode;
}

std_vector< std_pairt< QString, std_vector< QString > > > BaseNodeStack::permissionNodeType( ) const {
	size_t count = nodeGenerate->size( );
	if( count == 0 )
		return { };
	auto data = nodeGenerate->data( );
	std_vector< std_pairt< QString, std_vector< QString > > > result( count );
	auto targetDataPtr = result.data( );
	for( size_t index = 0; index < count; ++index )
		targetDataPtr[ index ] = data[ index ].first;
	return result;
}
