#include "./type_alias.h"

#include <QObject>

#include "../qt/tools/tools.h"
Imp_StaticMetaInfo( Type_Alias, QObject::tr( "Type_Alias" ), QObject::tr( "alias" ) );

bool nodeItemEnum::getEnumName( const Node_Item_Type &enum_var, QString &result_str ) {
	switch( enum_var ) {

		case Node_Item_Type::None :
			result_str = QObject::tr( "None" );
			return true;
		case Node_Item_Type::Root :
			result_str = QObject::tr( "Root" );
			return true;
		case Node_Item_Type::End :
			result_str = QObject::tr( "End" );
			return true;
		case Node_Item_Type::Process :
			result_str = QObject::tr( "Process" );
			return true;
		case Node_Item_Type::Logic :
			result_str = QObject::tr( "Logic" );
			return true;
		case Node_Item_Type::Foreach :
			result_str = QObject::tr( "Foreach" );
			return true;
		case Node_Item_Type::Loop :
			result_str = QObject::tr( "Loop" );
			return true;
	}

	tools::debug::printError( QString( "发现未知宏值 : %1" ).arg( ( size_t ) enum_var ) );
	return false;;
}
bool nodeItemEnum::getEnumName( const Click_Type &enum_var, QString &result_str ) {
	switch( enum_var ) {
		case Click_Type::None :
			result_str = QObject::tr( "None" );
			return true;
		case Click_Type::Space :
			result_str = QObject::tr( "Space" );
			return true;
		case Click_Type::Title :
			result_str = QObject::tr( "Title" );
			return true;
		case Click_Type::InputPort :
			result_str = QObject::tr( "InputPort" );
			return true;
		case Click_Type::OutputPort :
			result_str = QObject::tr( "OutputPort" );
			return true;
	}
	tools::debug::printError( QString( "发现未知宏值 : %1" ).arg( ( size_t ) enum_var ) );
	return false;;
}