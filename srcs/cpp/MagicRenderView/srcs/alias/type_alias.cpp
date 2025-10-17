#include "./type_alias.h"

#include <QObject>

#include "../qt/tools/tools.h"
Imp_StaticMetaInfo( Type_Alias, QObject::tr( "Type_Alias" ), QObject::tr( "alias" ) );

bool nodeItemEnum::getEnumName( const Node_Item_Type &enum_var, QString &result_str ) {
	switch( enum_var ) {

		case Node_Item_Type::None :
			result_str = QObject::tr( "无" );
			return true;
		case Node_Item_Type::Root :
			result_str = QObject::tr( "根" );
			return true;
		case Node_Item_Type::End :
			result_str = QObject::tr( "结束" );
			return true;
		case Node_Item_Type::Process :
			result_str = QObject::tr( "流程" );
			return true;
		case Node_Item_Type::Logic :
			result_str = QObject::tr( "逻辑" );
			return true;
		case Node_Item_Type::Foreach :
			result_str = QObject::tr( "循环" );
			return true;
		case Node_Item_Type::Loop :
			result_str = QObject::tr( "跳" );
			return true;
	}

	tools::debug::printError( QString( "发现未知宏值 : %1" ).arg( ( size_t ) enum_var ) );
	return false;;
}
bool nodeItemEnum::getEnumName( const Click_Type &enum_var, QString &result_str ) {
	switch( enum_var ) {
		case Click_Type::None :
			result_str = QObject::tr( "无" );
			return true;
		case Click_Type::Space :
			result_str = QObject::tr( "空白" );
			return true;
		case Click_Type::Title :
			result_str = QObject::tr( "标题" );
			return true;
		case Click_Type::InputPort :
			result_str = QObject::tr( "输入端" );
			return true;
		case Click_Type::OutputPort :
			result_str = QObject::tr( "输出端" );
			return true;
	}
	tools::debug::printError( QString( "发现未知宏值 : %1" ).arg( ( size_t ) enum_var ) );
	return false;;
}