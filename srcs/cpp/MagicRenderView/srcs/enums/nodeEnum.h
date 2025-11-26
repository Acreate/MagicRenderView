#ifndef NODEENUM_H_H_HEAD__FILE__
#define NODEENUM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace NodeEnum {
	enum class ErrorType {
		Param,
		Result,
		Run,
		Other
	};
	enum class AdviseType {
		Param,
		Result,
		Run,
		Other
	};
	enum class CreateType {
		MainWindow_Nullptr,
		MainWidget_Nullptr,
		DrawNodeWidget_Nullptr,
		DrawNodeWidget_Add,
		Node_Parent,
	};
	enum class NodeType {
		Begin,
		End,
		Generate,
		Point,
		Jump,
		Logic,
	};
	enum class NodeClickType {
		None,
		Titile,
		InputPort,
		OutputPort
	};
	bool converEnum( const QString &enum_string, ErrorType &result_enum_type_var );
	bool converEnum( const QString &enum_string, AdviseType &result_enum_type_var );
	bool converEnum( const QString &enum_string, CreateType &result_enum_type_var );
	bool converEnum( const QString &enum_string, NodeType &result_enum_type_var );
	bool converEnum( const QString &enum_string, NodeClickType &result_enum_type_var );
	bool converQString( const ErrorType &enum_type_var, QString &result_enum_string );
	bool converQString( const AdviseType &enum_type_var, QString &result_enum_string );
	bool converQString( const CreateType &enum_type_var, QString &result_enum_string );
	bool converQString( const NodeType &enum_type_var, QString &result_enum_string );
	bool converQString( const NodeClickType &enum_type_var, QString &result_enum_string );
	Q_NAMESPACE;
	Q_ENUM_NS( ErrorType );
	Q_ENUM_NS( AdviseType );
	Q_ENUM_NS( CreateType );
	Q_ENUM_NS( NodeType );
	Q_ENUM_NS( NodeClickType );
};

#endif // NODEENUM_H_H_HEAD__FILE__
