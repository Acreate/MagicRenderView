#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "alias/type_alias.h"

class ITypeObject;
class IFunctionDeclaration;
class INodeWidget : public QWidget {
	Q_OBJECT;
public:
	INodeWidget( QWidget *parent, const Qt::WindowFlags &f ): QWidget( parent, f ) {
	}
	/// @brief 调用一次该节点
	virtual void call( ) const = 0;
	/// @brief 连接到目标节点
	/// @param source_node_name 源节点名称
	/// @param target_node 目标节点对象
	/// @param link_target_name 目标变量名称
	/// @return 链接结果返回，成功返回 0
	virtual int32_t linkTarget(const QString& source_node_name, INodeWidget *target_node, const QString &link_target_name ) const = 0;
	/// @brief 获取链接到该节点的所有信息
	/// @param link_target_name 该节点名称
	/// @return 链接到该节点名称的节点列表
	virtual std_vector_pairt< INodeWidget *, QString > getLinkSourceNodes( const QString &link_target_name) const;
	/// @brief 获取链接源列表
	/// @return 链接源列表
	virtual std_vector_pairt< INodeWidget *, QString > getLinkSourceNodes( ) const;

};

#endif // INODEWIDGET_H_H_HEAD__FILE__
