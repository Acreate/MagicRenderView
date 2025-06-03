#ifndef NODEGRAPH_H_H_HEAD__FILE__
#define NODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
class NodeAddMenu;
class NodeGraph : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 节点添加菜单
	NodeAddMenu* nodeMenu;
public:
	NodeGraph( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeGraph()override;
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
