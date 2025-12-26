#ifndef NODEENUM_H_H_HEAD__FILE__
#define NODEENUM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace NodeEnum {
	/// @brief 错误类型
	enum class ErrorType {
		Param,
		Result,
		Run,
		Other
	};
	/// @brief 建议类型
	enum class AdviseType {
		Param,
		Result,
		Run,
		Other
	};
	/// @brief 创建的错误类型
	enum class CreateType {
		MainWindow_Nullptr,
		MainWidget_Nullptr,
		DrawNodeWidget_Nullptr,
		DrawNodeWidget_Add,
		Node_Parent,
	};
	/// @brief 节点类型
	enum class NodeType {
		InterFace,
		Begin,
		End,
		Generate,
		Point,
		Jump,
		Logic,
		Process,
		Cache,
		Array,
		Unity,
	};
	/// @brief 输入类型
	enum class PortType {
		InterFace,
		Generate,
		Unity,
		Array
	};
	/// @brief 点击节点返回类型
	enum class NodeClickType {
		None,
		Titile,
		InputPort,
		OutputPort
	};
	/// @brief 节点样式
	enum class NodeStyleType {
		None,
		Call_Function,
		Create,
		Select_Active,
		Select_Old,
		Select_Output_Ref,
		Select_Input_Ref,
		Warning,
		Error,
		Advise
	};
	bool converEnum( const QString &enum_string, ErrorType &result_enum_type_var );
	bool converEnum( const QString &enum_string, AdviseType &result_enum_type_var );
	bool converEnum( const QString &enum_string, CreateType &result_enum_type_var );
	bool converEnum( const QString &enum_string, NodeType &result_enum_type_var );
	bool converEnum( const QString &enum_string, NodeClickType &result_enum_type_var );
	bool converEnum( const QString &enum_string, NodeStyleType &result_enum_type_var );
	bool converQString( const ErrorType &enum_type_var, QString &result_enum_string );
	bool converQString( const AdviseType &enum_type_var, QString &result_enum_string );
	bool converQString( const CreateType &enum_type_var, QString &result_enum_string );
	bool converQString( const NodeType &enum_type_var, QString &result_enum_string );
	bool converQString( const NodeClickType &enum_type_var, QString &result_enum_string );
	bool converQString( const NodeStyleType &enum_type_var, QString &result_enum_string );
	Q_NAMESPACE;
	Q_ENUM_NS( ErrorType );
	Q_ENUM_NS( AdviseType );
	Q_ENUM_NS( CreateType );
	Q_ENUM_NS( NodeType );
	Q_ENUM_NS( NodeClickType );
	Q_ENUM_NS( NodeStyleType );
};

#endif // NODEENUM_H_H_HEAD__FILE__
