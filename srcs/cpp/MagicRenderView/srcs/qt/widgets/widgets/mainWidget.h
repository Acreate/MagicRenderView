#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeScriptsScrollAreasWidget;
class NodeListScrollAreasWidget;
class NodeRenderScrollAreasWidget;
class MainWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 节点渲染窗口
	NodeRenderScrollAreasWidget *nodeRenderWidget;
	/// @brief 节点罗列列表
	NodeListScrollAreasWidget *nodeListWidget;
	/// @brief 节点执行列表
	NodeScriptsScrollAreasWidget *nodeScriptsWidget;
public:
	MainWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void updateResize( );
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
