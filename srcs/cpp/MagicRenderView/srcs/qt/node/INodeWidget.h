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
	/// @param target_node 目标节点对象
	/// @param link_target_name 目标变量名称
	/// @param link_result 链接结果返回，成功返回 0
	/// @return 如果该节点为单向节点，那么返回上次链接对象，或返回断开链接对象
	virtual const INodeWidget * linkTarget( INodeWidget *target_node, const QString &link_target_name, int32_t &link_result ) const = 0;
	/// @brief 获取链接源列表
	/// @return 链接源列表
	virtual std_vector_pairt< INodeWidget *, QString > getLinkSourceNode( ) const;

};

#endif // INODEWIDGET_H_H_HEAD__FILE__
