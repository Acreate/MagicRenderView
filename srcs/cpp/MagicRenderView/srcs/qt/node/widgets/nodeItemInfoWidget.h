#ifndef NODEITEMINFOWIDGET_H_H_HEAD__FILE__
#define NODEITEMINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include "nodeItemInfoScrollAreaWidget.h"

#include <alias/type_alias.h>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class NodeItem;
class NodeItemInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItemTarget;
	bool updateOver;
	/// @brief 主要布局
	QVBoxLayout *mainLayout;
	/// @brief 标题窗口
	QWidget *titileWidget;
	/// @brief 创建变量的菜单
	QMenu* createVarItemMenu;
public:
	NodeItemInfoWidget( NodeItem *node_item, QWidget *parent = nullptr );
	virtual NodeItem * getNodeItemTarget( ) const { return nodeItemTarget; }
	virtual void setNodeItemTarget( NodeItem *node_item_target );
	virtual void resetUpdataStats( ) { updateOver = false; }
protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEITEMINFOWIDGET_H_H_HEAD__FILE__
