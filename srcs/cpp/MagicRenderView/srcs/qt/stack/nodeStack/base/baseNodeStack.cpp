#include "./baseNodeStack.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/node/nodeWidget/base/nodeFileInfo.h"

#define emplace_back_NodeGenerate( type_, ... ) \
	nodeGenerate->emplace_back( std_pairt( NodeFileInfo::staticMetaObject.className(  ), std_vector< QString >({ __VA_ARGS__ } ) ), []( const std_shared_ptr<IFunctionDeclaration>& p )->INodeWidget * {\
		type_ *nodeWidgetPtr = new type_;\
		auto name = nodeWidgetPtr->metaObject( )->className( );\
		nodeWidgetPtr->setObjectName( name );\
		nodeWidgetPtr->setWindowTitle( name );\
		return nodeWidgetPtr;\
	} )

BaseNodeStack::BaseNodeStack( ) : nodeGenerate( new std_vector< generateNodePairt >( ) ) {
	emplace_back_NodeGenerate( NodeFileInfo, "fileInfo" );
}
INodeWidget * BaseNodeStack::_newNode( const QString &type_name, const std_shared_ptr< IFunctionDeclaration > &function_declarction ) const {
	size_t count = nodeGenerate->size( );
	if( count == 0 )
		return nullptr;
	auto data = nodeGenerate->data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first.first == type_name )
			return data[ index ].second( function_declarction );
		else
			for( auto &key : data[ index ].first.second )
				if( key == type_name )
					return data[ index ].second( function_declarction );
	return nullptr;
}
INodeWidget * BaseNodeStack::generateNode( const QString &type_name, QWidget *parnet, const std_shared_ptr< IFunctionDeclaration > &function_declaration ) const {
	INodeWidget *newNode = _newNode( type_name, function_declaration );
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
