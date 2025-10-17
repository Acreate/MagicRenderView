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
		Root, // 根，节点运行必须在连接的根源存在根节点，具备循环权与运行权节点
		End, // 尾，节点链表结束节点，具备整个节点运行结束的能力。运行到该节点，总会结束整个节点链
		Process, // 过程，一般的调度节点，自身不具备运行能力
		Logic, // 逻辑，具备选择输出权，自身不具备运行能力
		Point, // 点，记录节点，自身不具备运行能力
		Jump, // 回路，运行该节点之后，整个渲染流程回到最近的 Point 权节点，具备完整跳转权。
	};
	Q_ENUM_NS( Node_Item_Type );
	bool getEnumName( const Node_Item_Type &enum_var, QString &result_str );
	bool getEnumName( const Click_Type &enum_var, QString &result_str );
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
