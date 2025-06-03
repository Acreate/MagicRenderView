#ifndef NODEADDMENU_H_H_HEAD__FILE__
#define NODEADDMENU_H_H_HEAD__FILE__
#pragma once

#include <QMenu>

class NodeAddAction;
class NodeAddMenu : public QMenu {
	Q_OBJECT;
public:
	NodeAddMenu( QWidget *parent );
	NodeAddMenu( const QString &title = "", QWidget *parent = nullptr )
		: NodeAddMenu( parent ) { }
	~NodeAddMenu() override;
Q_SIGNALS:
	/// @brief 选项被正式激活
	/// @param node_add_acton 激活选项
	void activeNodeAction( const NodeAddAction *node_add_acton );
	/// @brief 选项被正式激活
	/// @param action 激活选项
	void activeQAction( const QAction *action );
};

#endif // NODEADDMENU_H_H_HEAD__FILE__
