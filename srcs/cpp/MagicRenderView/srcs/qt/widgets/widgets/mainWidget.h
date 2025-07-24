#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

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
	/// @brief 渲染窗口比例
	std_pairt< QString, size_t > renderLayout;
	/// @brief 节点列表比例
	std_pairt< QString, size_t > nodeListLayout;
	/// @brief 节点脚本比例
	std_pairt< QString, size_t > nodeScriptsLayout;
public:
	MainWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void updateResize( );
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
