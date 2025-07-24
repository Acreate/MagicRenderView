#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

class QVBoxLayout;
class Application;
class NodeScriptsScrollAreasWidget;
class NodeListScrollAreasWidget;
class NodeRenderScrollAreasWidget;
class MainWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 节点渲染窗口
	NodeRenderScrollAreasWidget *nodeRenderWidget;
	/// @brief 节点罗列列表
	NodeListScrollAreasWidget *nodeListWidget;
	/// @brief 节点执行列表
	NodeScriptsScrollAreasWidget *nodeScriptsWidget;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 鼠标是否按下
	bool mouseIsPress;
	/// @brief 拖拽拉伸窗口大小
	QWidget *dragWidgetSize;
	/// @brief 当前鼠标图标
	Qt::CursorShape cursorShape;
public:
	MainWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	/// @brief 初始化子窗口布局
	virtual void initWidgetListLayout( );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
