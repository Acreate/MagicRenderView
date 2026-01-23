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
	/// @brief 节点状态样式
	enum class NodeStatusType {
		/// @brief 无状态
		None,
		/// @brief 创建
		Create,
		/// @brief 节点正在运行
		Current_Run,
		/// @brief 节点警告
		Warning,
		/// @brief 节点错误
		Error,
		/// @brief 节点建议
		Advise
	};
	/// @brief 节点选择样式
	enum class NodeSelctType {
		/// @brief 没有选择
		None,
		/// @brief 当前选择
		Select_Active,
		/// @brief 以前选择
		Select_Old,
		/// @brief 选择输出
		Select_Output_Ref,
		/// @brief 选择输入
		Select_Input_Ref,
	};

	Q_NAMESPACE;
	Q_ENUM_NS( ErrorType );
	Q_ENUM_NS( AdviseType );
	Q_ENUM_NS( CreateType );
	Q_ENUM_NS( NodeType );
	Q_ENUM_NS( NodeClickType );
	Q_ENUM_NS( NodeStatusType );
	Q_ENUM_NS( PortType );
	Q_ENUM_NS( NodeSelctType );

};

#endif // NODEENUM_H_H_HEAD__FILE__
