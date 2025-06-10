#include "./baseNodeStack.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/node/nodeWidget/base/nodeFileInfo.h"

#define emplace_back_NodeGenerate( type_, parent_, window_flags_, first_name_, ... ) \
	nodeGenerate->emplace_back( std_pairt( first_name_, std_vector< QString >({ NodeFileInfo::staticMetaObject.className(  ),__VA_ARGS__ } ) ), [](  )->INodeWidget * {\
		type_ *nodeWidgetPtr = new type_(first_name_, parent_, window_flags_);\
		return nodeWidgetPtr;\
	} )

BaseNodeStack::BaseNodeStack( ) : nodeGenerate( new std_vector< generateNodePairt >( ) ) {
	setObjectName( BaseNodeStack::staticMetaObject.className( ) );

	emplace_back_NodeGenerate( NodeFileInfo, nullptr, Qt::WindowFlags(), "文件信息节点" );
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

std_vector< std_pairt< std_pairt< QString, std_vector< QString > >, std_function< void( ) > > > BaseNodeStack::permissionNodeType( ) const {
	size_t count = nodeGenerate->size( );
	if( count == 0 )
		return { };
	auto data = nodeGenerate->data( );
	std_vector< std_pairt< std_pairt< QString, std_vector< QString > >, std_function< void( ) > > > result( count );
	auto targetDataPtr = result.data( );
	for( size_t index = 0; index < count; ++index )
		targetDataPtr[ index ].first = data[ index ].first;
	return result;
}
