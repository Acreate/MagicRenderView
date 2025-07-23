#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
class NodeScriptsWidget;
class NodeListWidget;
class NodeRenderWidget;
class MainWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 节点渲染窗口
	NodeRenderWidget *nodeRenderWidget;
	/// @brief 节点罗列列表
	NodeListWidget* nodeListWidget;
	/// @brief 节点执行列表
	NodeScriptsWidget*  nodeScriptsWidget;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
