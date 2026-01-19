#ifndef NODEENUM_H_H_HEAD__FILE__
#define NODEENUM_H_H_HEAD__FILE__

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
		Point,
		Jump,
		Logic,
		Process
	};
	/// @brief 端口类型
	enum class PortType {
		Unity,
		AnyVar,
		Array,
		Point,
		ToPoint,
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
		Create,
		Current_Run,
		Warning,
		Error,
		Advise
	};
	/// @brief 节点样式
	enum class NodeSelctType {
		None,
		Select_Active,
		Select_Old,
		Select_Output_Ref,
		Select_Input_Ref,
	};

	Q_NAMESPACE;
	Q_ENUM_NS( ErrorType );
	Q_ENUM_NS( AdviseType );
	Q_ENUM_NS( CreateType );
	Q_ENUM_NS( NodeType );
	Q_ENUM_NS( NodeClickType );
	Q_ENUM_NS( NodeStyleType );
	Q_ENUM_NS( PortType );
	Q_ENUM_NS( NodeSelctType );

};

#endif // NODEENUM_H_H_HEAD__FILE__
