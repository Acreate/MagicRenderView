#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>
class INodeWidget;
class INodeComponent;
class NodeGraph;
class Application : public QApplication {
	Q_OBJECT;
public: // 类型
	enum class MouseEventType {
		Init, // 初始化
		Press, // 按下
		Release, // 释放
		Move,// 移动
	};
protected:
	/// @brief 渲染面板
	static NodeGraph *mainNodeGraph;
public:
	/// @brief 把全部窗口移动到指定显示器上
	/// @param index 显示器序列
	static void setWindowToIndexScreenCentre( size_t index );
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	/// @brief 配置渲染面板
	/// @param node_graph 渲染面板
	/// @return 旧的渲染面板
	static NodeGraph * setNewNodeGraph( NodeGraph *node_graph ) {
		auto oldNodeGraph = mainNodeGraph;
		mainNodeGraph = node_graph;
		return oldNodeGraph;
	}
	static size_t getID( const INodeWidget *node_widget );
public:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
