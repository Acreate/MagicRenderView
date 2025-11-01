#include "nodeItemEnum.h"

#include <qt/tools/tools.h>

bool nodeItemEnum::getEnumName( const Node_Item_Type &enum_var, QString &result_str ) {
	switch( enum_var ) {

		case Node_Item_Type::None :
			result_str = QObject::tr( "无" );
			return true;
		case Node_Item_Type::Begin :
			result_str = QObject::tr( "开始" );
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
		case Node_Item_Type::Mark :
			result_str = QObject::tr( "点" );
			return true;
		case Node_Item_Type::Jump :
			result_str = QObject::tr( "跳" );
			return true;
		case Node_Item_Type::GenerateVar :
			result_str = QObject::tr( "生成" );
			return true;
		case Node_Item_Type::ReleaseVar :
			result_str = QObject::tr( "释放" );
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
bool nodeItemEnum::getEnumName( const Node_Item_Builder_Type &enum_var, QString &result_str ) {

	switch( enum_var ) {
		case Node_Item_Builder_Type::None :
			result_str = QObject::tr( "未定义" );
			return true;
		case Node_Item_Builder_Type::Warning :
			result_str = QObject::tr( "警告" );
			return true;
		case Node_Item_Builder_Type::Error :
			result_str = QObject::tr( "错误" );
			return true;
		case Node_Item_Builder_Type::Finish :
			result_str = QObject::tr( "完成" );
			return true;
		case Node_Item_Builder_Type::Last :
			result_str = QObject::tr( "末尾" );
			return true;
		case Node_Item_Builder_Type::Start :
			result_str = QObject::tr( "起始" );
			return true;
	}
	tools::debug::printError( QString( "发现未知宏值 : %1" ).arg( ( size_t ) enum_var ) );
	return false;;
}
