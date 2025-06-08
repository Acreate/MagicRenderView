#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class NodeGraph;
class INodeComponent;
class INodeWidget : public QWidget {
	Q_OBJECT;
public:
	/// @brief QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()
	/// @param parent 父节点，用于 qt 内存管理系统。
	/// @param f 窗口风格
	INodeWidget( QWidget *parent, Qt::WindowFlags f ) { }
	/// @brief 信号连接到指定窗口
	/// @param node_graph 响应信号的窗口
	virtual void connectNodeGraphWidget( NodeGraph *node_graph );
Q_SIGNALS:
	/// @brief 选中窗口时候除法该信号
	/// @param select_node_component 当命中组件时，该指针不为 nullptr
	void selectNodeWidgetBody( INodeComponent *select_node_component );
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
