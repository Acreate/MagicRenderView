#ifndef NODELINKITEM_H_H_HEAD__FILE__
#define NODELINKITEM_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

class INodeWidget;
class INodeComponent;
class NodeLinkItem : public QObject {
	Q_OBJECT;
protected:
	/// @brief 输出链接项目
	std_pairt< INodeWidget *, INodeComponent * > input_node_component_info;
	/// @brief 输入链接项目
	std_pairt< INodeWidget *, INodeComponent * > output_node_component_info;
public:
	NodeLinkItem( ) {
	}
	NodeLinkItem( const NodeLinkItem &other )
		: QObject( other.parent( ) ),
		input_node_component_info( other.input_node_component_info ),
		output_node_component_info( other.output_node_component_info ) { }
	NodeLinkItem & operator=( const NodeLinkItem &other ) {
		if( this == &other )
			return *this;
		setParent( other.parent( ) );
		input_node_component_info = other.input_node_component_info;
		output_node_component_info = other.output_node_component_info;
		return *this;
	}
	virtual bool operator==( const NodeLinkItem &right ) const {
		auto rightNodeLinkItemPtr = &right;
		if( this == rightNodeLinkItemPtr )
			return true;
		auto *rightInputNodeComponentInfo = &right.input_node_component_info;
		if( rightInputNodeComponentInfo->first != input_node_component_info.first ||
			rightInputNodeComponentInfo->second != input_node_component_info.second )
			return false;
		rightInputNodeComponentInfo = &right.output_node_component_info;
		if( rightInputNodeComponentInfo->first != output_node_component_info.first ||
			rightInputNodeComponentInfo->second != output_node_component_info.second )
			return false;
		return true;
	}
	virtual bool operator!=( const NodeLinkItem &right ) const {
		return !NodeLinkItem::operator==( right );
	}
	/// @brief 配置输入
	/// @param input_node_widget 输入节点
	/// @param input_node_component 输入组件
	/// @return 成功返回 true
	virtual bool setInput( INodeWidget *input_node_widget, INodeComponent *input_node_component );
	/// @brief 配置输出
	/// @param output_node_widget 输出节点
	/// @param output_node_component 输出组件
	/// @return 成功配置返回 true
	virtual bool setOutput( INodeWidget *output_node_widget, INodeComponent *output_node_component );
	/// @brief 重置
	virtual void setNullptr( ) {
		output_node_component_info = input_node_component_info = { nullptr, nullptr };
	}
	/// @brief 获取输出输入组件的坐标
	/// @param result_input_component_pos 返回输入的组件位置
	/// @param result_output_component_pos 返回输出的组件位置
	/// @return 成功返回 true
	virtual bool getInputOutputPos( QPoint *result_input_component_pos, QPoint *result_output_component_pos ) const;
};

#endif // NODELINKITEM_H_H_HEAD__FILE__
