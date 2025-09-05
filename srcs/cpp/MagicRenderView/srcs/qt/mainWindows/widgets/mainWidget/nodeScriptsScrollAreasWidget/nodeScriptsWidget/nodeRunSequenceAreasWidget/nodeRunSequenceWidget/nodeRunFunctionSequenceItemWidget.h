#ifndef NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#define NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../nodeRunSequenceWidget.h"

class NodeRunFunctionSequenceItemWidget : public QWidget {
	Q_OBJECT;
public:
	friend class NodeRunSequenceWidget;
protected:
	/// @brief 是否显示子节点
	bool showChildStatus = false;
	/// @brief 节点是否有效
	bool itemActive = false;
	NodeRunSequenceWidget *itemParent;
protected:
	NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration );
public:
	virtual bool isShowChild( ) const {
		return showChildStatus;
	}
	virtual bool isItemActve( ) const {
		return itemActive;
	}
	~NodeRunFunctionSequenceItemWidget()override;
Q_SIGNALS:
	/// @brief 显示子节点
	/// @param flag true 表示展开，false 表示收缩
	void showStatusChange( bool flag );
	/// @brief 展开选项
	bool expandItem( );
	/// @brief 收缩项
	bool shrinkage( );
	/// @brief 对象销毁时触发该消息
	/// @param delete_obj_ptr 销毁指针
	void thisObjectDestory(NodeRunFunctionSequenceItemWidget* delete_obj_ptr);
};

#endif // NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
