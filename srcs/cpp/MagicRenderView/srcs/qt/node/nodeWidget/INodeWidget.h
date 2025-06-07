#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class INodeComponent;
class INodeWidget : public QWidget {
	Q_OBJECT;
public:
	INodeWidget( ) { }
Q_SIGNALS:
	/// @brief 选中窗口时候除法该信号
	/// @param select_node_component 当命中组件时，该指针不为 nullptr
	void selectNodeWidgetBody(INodeComponent *select_node_component);
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
