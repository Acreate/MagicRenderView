#include "./baseInfoWidgetStack.h"

#include <qt/widget/infoWidget/IInfoWidget.h>

#include <qt/widget/infoWidget/infoBaseWidget/textWidget.h>

#include "../../../widget/infoWidget/infoBaseWidget/errorMsgWidget.h"

#define emplace_back_InfoWidget( type_, titile) \
	infoWidgetGenerate->emplace_back( generateInfoWidgetPairt( { type_::staticMetaObject.className( ), { titile } }, [this]( ) ->IInfoWidget * {	return new type_( getStackFunction, nullptr, titile );	} ) )

BaseInfoWidgetStack::BaseInfoWidgetStack( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function ): IInfoWidgetStack( get_stack_function ), infoWidgetGenerate( new std_vector< generateInfoWidgetPairt > ) {
	stackTypeNames.clear( );
	stackTypeNames.emplace_back( "常规窗口" );
	emplace_back_InfoWidget( TextWidget, "文本" );
	emplace_back_InfoWidget( ErrorMsgWidget, "错误" );
}
IInfoWidget * BaseInfoWidgetStack::_newNode( const QString &type_name ) const {
	size_t count = infoWidgetGenerate->size( );
	if( count == 0 )
		return nullptr;
	auto data = infoWidgetGenerate->data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first.first == type_name )
			return data[ index ].second( );
		else
			for( auto &key : data[ index ].first.second )
				if( key == type_name )
					return data[ index ].second( );
	return nullptr;
}
IInfoWidget * BaseInfoWidgetStack::generateInfoWidget( const QString &type_name, QWidget *parnet ) const {
	IInfoWidget *newNode = _newNode( type_name );
	if( newNode )
		newNode->setParent( parnet );
	return newNode;
}
std_vector< std_pairt< QString, std_vector< QString > > > BaseInfoWidgetStack::permissionInfoWidget( ) const {
	size_t count = infoWidgetGenerate->size( );
	if( count == 0 )
		return { };
	auto data = infoWidgetGenerate->data( );
	std_vector< std_pairt< QString, std_vector< QString > > > result( count );
	auto targetDataPtr = result.data( );
	for( size_t index = 0; index < count; ++index )
		targetDataPtr[ index ] = data[ index ].first;
	return result;
}
