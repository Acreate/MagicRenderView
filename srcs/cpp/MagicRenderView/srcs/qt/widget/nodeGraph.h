#ifndef NODEGRAPH_H_H_HEAD__FILE__
#define NODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
class INodeComponent;
class QLabel;
class NodeAddMenu;
class NodeGraph : public QWidget {
	Q_OBJECT;
private: // 私有类型
	enum class MouseEventType {
		Init, // 初始化
		Press, // 按下
		Release, // 释放
		Move,// 移动
	};
protected:
	/// @brief 节点添加菜单
	NodeAddMenu *nodeMenu;
	/// @brief 用于显示鼠标位置
	QLabel *mousePosLabel;
	/// @brief 当前鼠标状态
	MouseEventType mouseEventStatus;

	// 鼠标全局位置
	QPoint cursorPos;
	// 鼠标窗口位置
	QPoint currentMouseInWidgetPos;
public:
	NodeGraph( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeGraph( ) override;
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
public Q_SLOTS:
	void selectNodeWidgetBody( INodeComponent *select_node_component );
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
