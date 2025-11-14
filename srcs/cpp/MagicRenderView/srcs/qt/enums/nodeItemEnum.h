#ifndef NODEITEMENUM_H_H_HEAD__FILE__
#define NODEITEMENUM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace nodeItemEnum {
	Q_NAMESPACE;
	enum class Click_Type {
		None, // 没有
		Space, // 空白
		Title, // 标题
		InputPort, // 输入
		OutputPort, // 输出
	};
	Q_ENUM_NS( Click_Type );

	enum class Node_Item_Type {
		None, // 非正式
		Begin, // 根
		End, // 尾
		GenerateVar, // 生成，当输出为 nullptr 时，终结进程
		ReleaseVar, // 释放，当输出为 nullptr 时，终结进程
		Process, // 过程
		Logic, // 逻辑
		Mark, // 点，记录节点
		Jump, // 回路，运行该节点之后，整个渲染流程回到最近的 Point 权节点，具备完整跳转权。
	};
	Q_ENUM_NS( Node_Item_Type );

	enum class Node_Item_Result_Type {
		/// @brief 没实现
		NotImplementation,
		/// @brief 正确返回
		Finish,
		/// @brief 参数异常
		Param_Error,
	};
	Q_ENUM_NS( Node_Item_Result_Type );

	enum class Node_Item_Builder_Type {
		None,
		Warning,
		Error,
		Finish,
		Last,
		Start,
	};
	Q_ENUM_NS( Node_Item_Builder_Type );

	bool getEnumName( const Node_Item_Type &enum_var, QString &result_str );
	bool getEnumName( const Click_Type &enum_var, QString &result_str );
	bool getEnumName( const Node_Item_Builder_Type &enum_var, QString &result_str );
}

#define Def_First_Mate_Node_Type( node_Item_enum_type_value ) \
	public: \
	virtual nodeItemEnum::Node_Item_Type getNodeMetaType( ) const { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; } \
	static nodeItemEnum::Node_Item_Type getStaticMetaNodeType( ) { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; }

#define Def_Last_Mate_Node_Type( node_Item_enum_type_value ) \
	public: \
	nodeItemEnum::Node_Item_Type getNodeMetaType( ) const override { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; } \
	static nodeItemEnum::Node_Item_Type getStaticMetaNodeType( ) { return nodeItemEnum::Node_Item_Type::node_Item_enum_type_value; }

#endif // NODEITEMENUM_H_H_HEAD__FILE__
