#include "nodeEnum.h"

#include <QMetaEnum>
bool NodeEnum::converEnum( const QString &enum_string, ErrorType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< ErrorType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( ErrorType ) *varPtr;
	switch( result_enum_type_var ) {
		case ErrorType::Param :
		case ErrorType::Result :
		case ErrorType::Run :
		case ErrorType::Other :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, AdviseType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< AdviseType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( AdviseType ) *varPtr;
	switch( result_enum_type_var ) {

		case AdviseType::Param :
		case AdviseType::Result :
		case AdviseType::Run :
		case AdviseType::Other :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, CreateType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< CreateType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( CreateType ) *varPtr;
	switch( result_enum_type_var ) {
		case CreateType::MainWindow_Nullptr :
		case CreateType::MainWidget_Nullptr :
		case CreateType::DrawNodeWidget_Nullptr :
		case CreateType::DrawNodeWidget_Add :
		case CreateType::Node_Parent :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, NodeType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< NodeType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( NodeType ) *varPtr;
	switch( result_enum_type_var ) {
		case NodeType::Begin :
		case NodeType::End :
		case NodeType::Generate :
		case NodeType::Point :
		case NodeType::Jump :
		case NodeType::Logic :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, NodeClickType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< NodeType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( NodeClickType ) *varPtr;
	switch( result_enum_type_var ) {
		case NodeClickType::None :
		case NodeClickType::Titile :
		case NodeClickType::InputPort :
		case NodeClickType::OutputPort :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, NodeStyleType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< NodeType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( NodeStyleType ) *varPtr;
	switch( result_enum_type_var ) {
		case NodeStyleType::None :
		case NodeStyleType::Create :
		case NodeStyleType::Call_Function :
		case NodeStyleType::Advise :
		case NodeStyleType::Error :
		case NodeStyleType::Select_Active :
		case NodeStyleType::Select_Old :
		case NodeStyleType::Warning :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converEnum( const QString &enum_string, PortType &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< NodeType >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );

	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( PortType ) *varPtr;
	switch( result_enum_type_var ) {
		case PortType::InterFace :
		case PortType::Generate :
		case PortType::Unity :
		case PortType::Array :
		case PortType::ToBegin :
		case PortType::Begin :
		case PortType::Point :
		case PortType::ToPoint :
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const PortType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case PortType::InterFace :
			result_enum_string = "InterFace";
			break;
		case PortType::Generate :
			result_enum_string = "Generate";
			break;
		case PortType::Array :
			result_enum_string = "Array";
			break;
		case PortType::ToBegin :
			result_enum_string = "ToBegin";
			break;
		case PortType::Begin :
			result_enum_string = "Begin";
			break;
		case PortType::Unity :
			result_enum_string = "Unity";
			break;
		case PortType::Point :
			result_enum_string = "Point";
			break;
		case PortType::ToPoint :
			result_enum_string = "ToPoint";
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const NodeStyleType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case NodeStyleType::None :
			result_enum_string = "None";
			break;
		case NodeStyleType::Select_Active :
			result_enum_string = "Select_Active";
			break;
		case NodeStyleType::Select_Old :
			result_enum_string = "Select_Old";
			break;
		case NodeStyleType::Warning :
			result_enum_string = "Warning";
			break;
		case NodeStyleType::Error :
			result_enum_string = "Error";
			break;
		case NodeStyleType::Advise :
			result_enum_string = "Advise";
			break;
		case NodeStyleType::Call_Function :
			result_enum_string = "Call_Function";
			break;
		case NodeStyleType::Create :
			result_enum_string = "Create";
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const ErrorType &enum_type_var, QString &result_enum_string ) {

	switch( enum_type_var ) {
		case ErrorType::Param :
			result_enum_string = "Param";
			break;
		case ErrorType::Result :
			result_enum_string = "Result";
			break;
		case ErrorType::Run :
			result_enum_string = "Run";
			break;
		case ErrorType::Other :
			result_enum_string = "Other";
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const AdviseType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case AdviseType::Param :
			result_enum_string = "Param";
			break;
		case AdviseType::Result :
			result_enum_string = "Result";
			break;
		case AdviseType::Run :
			result_enum_string = "Run";
			break;
		case AdviseType::Other :
			result_enum_string = "Other";
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const CreateType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case CreateType::MainWindow_Nullptr :
			result_enum_string = "MainWindow_Nullptr";
			break;
		case CreateType::MainWidget_Nullptr :
			result_enum_string = "MainWidget_Nullptr";
			break;
		case CreateType::DrawNodeWidget_Nullptr :
			result_enum_string = "DrawNodeWidget_Nullptr";
			break;
		case CreateType::DrawNodeWidget_Add :
			result_enum_string = "DrawNodeWidget_Add";
			break;
		case CreateType::Node_Parent :
			result_enum_string = "Node_Parent";
			break;
		default :
			return false;
	}
	return true;
}
bool NodeEnum::converQString( const NodeType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case NodeType::Begin :
			result_enum_string = "Begin";
			break;
		case NodeType::End :
			result_enum_string = "End";
			break;
		case NodeType::Generate :
			result_enum_string = "Generate";
			break;
		case NodeType::Point :
			result_enum_string = "Point";
			break;
		case NodeType::Jump :
			result_enum_string = "Jump";
			break;
		case NodeType::Logic :
			result_enum_string = "Logic";
			break;
		default :
			return false;
	}
	return true;
}

bool NodeEnum::converQString( const NodeClickType &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {

		case NodeClickType::None :
			result_enum_string = "None";
			break;
		case NodeClickType::Titile :
			result_enum_string = "Titile";
			break;
		case NodeClickType::InputPort :
			result_enum_string = "InputPort";
			break;
		case NodeClickType::OutputPort :
			result_enum_string = "OutputPort";
			break;
		default :
			return false;
	}
	return true;
}
