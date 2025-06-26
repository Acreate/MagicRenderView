#include "./baseInfoWidgetStack.h"

#include <qt/widget/infoWidget/IInfoWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/combinationWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/dataWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/errorMsgWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/floatWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/intWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/pairtWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/stringWidget.h>
#include <qt/widget/infoWidget/infoBaseWidget/vectorWidget.h>
#include <qt/widget/infoWidget/superInfoWidget/pathWidget.h>

#include "../../../type/ITypeObject.h"

#define emplace_back_InfoWidget( type_, titile, ...) \
	infoWidgetGenerate->emplace_back( generateInfoWidgetPairt( { type_::staticMetaObject.className( ), { titile , __VA_ARGS__ } }, [this]( ) ->IInfoWidget * {	return new type_( getStackFunction, nullptr, titile );	} ) )

BaseInfoWidgetStack::BaseInfoWidgetStack( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function ): IInfoWidgetStack( get_stack_function ), infoWidgetGenerate( new std_vector< generateInfoWidgetPairt > ) {
	stackTypeNames.clear( );
	stackTypeNames.emplace_back( "常规窗口" );
	emplace_back_InfoWidget( StringWidget, "文本", "字符串" );
	emplace_back_InfoWidget( PathWidget, "路径" );
	emplace_back_InfoWidget( IntWidget, "整数" );
	emplace_back_InfoWidget( FloatWidget, "浮点", "浮点数" );
	emplace_back_InfoWidget( VectorWidget, "列表", "数组" );
	emplace_back_InfoWidget( DataWidget, "二进制", "数据" );
	emplace_back_InfoWidget( CombinationWidget, "混合", "结构体" );
	emplace_back_InfoWidget( PairtWidget, "配对", "键值对" );

	emplace_back_InfoWidget( PathWidget, "路径" );

	emplace_back_InfoWidget( ErrorMsgWidget, "错误", "空", "nullptr", "提示", "null", "void", "NULL" );
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
IInfoWidget * BaseInfoWidgetStack::generateInfoWidget( const std_shared_ptr< ITypeObject > &type_name, QWidget *parnet ) const {
	std_vector< QString > names = type_name.get( )->getUiTypeNames( );
	for( auto name : names ) {
		auto infoWidget = generateInfoWidget( name, parnet );
		if( infoWidget != nullptr )
			return infoWidget;
	}
	return nullptr;
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
