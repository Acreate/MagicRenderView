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
	/// @brief 校验是否存在指定组件
	/// @param component 匹配的组件指针
	/// @return 返回 1 表示存在输入，返回 -1 表示存在输出，返回 0 表示不存在组件
	virtual int has( const INodeComponent *component ) const {
		if( input_node_component_info.second == component )
			return 1;
		if( output_node_component_info.second == component )
			return -1;
		return 0;
	}
	/// @brief 校验是否存在指定节点
	/// @param node_widget 匹配的节点指针
	/// @return 返回 1 表示存在输入，返回 -1 表示存在输出，返回 0 表示不存在
	virtual int has( const INodeWidget *node_widget ) const {
		if( input_node_component_info.first == node_widget )
			return 1;
		if( output_node_component_info.first == node_widget )
			return -1;
		return 0;
	}

	/// @brief 校验是否存在指定输入组件
	/// @param component 匹配的输入组件指针
	/// @return 返回 false 表示不存在组件
	virtual bool hasInput( const INodeComponent *component ) const {
		if( input_node_component_info.second == component )
			return true;
		return false;
	}
	/// @brief 校验是否存在指定节点
	/// @param node_widget 匹配的输入节点指针
	/// @return 返回 false 表示不存在
	virtual bool hasInput( const INodeWidget *node_widget ) const {
		if( input_node_component_info.first == node_widget )
			return true;
		return false;
	}
	/// @brief 校验是否存在指定组件
	/// @param component 匹配的组件指针
	/// @return 返回 false 表示不存在
	virtual bool hasOutput( const INodeComponent *component ) const {
		if( output_node_component_info.second == component )
			return true;
		return false;
	}
	/// @brief 校验是否存在指定节点
	/// @param node_widget 匹配的节点指针
	/// @return 返回 false 表示不存在
	virtual bool hasOutput( const INodeWidget *node_widget ) const {
		if( output_node_component_info.first == node_widget )
			return true;
		return false;
	}

	virtual NodeLinkItem & operator=( const NodeLinkItem &other ) {
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
	virtual const std_pairt< INodeWidget *, INodeComponent * > & getInputNodeComponentInfo( ) const { return input_node_component_info; }
	virtual const std_pairt< INodeWidget *, INodeComponent * > & getOutputNodeComponentInfo( ) const { return output_node_component_info; }
};

#endif // NODELINKITEM_H_H_HEAD__FILE__
