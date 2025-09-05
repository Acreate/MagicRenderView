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
	/// @brief 当前鼠标
	QCursor* currentCursor;
	/// @brief 常规鼠标
	QCursor nCursor;
	/// @brief 垂直鼠标
	QCursor vCursor;
	/// @brief 水平鼠标
	QCursor hCursor;
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
protected:
	/// @brief 初始化子窗口布局
	void updateWidgetListLayout( const QSize &old_size, const QSize &current_size );
	/// @brief 写入高度
	void writeHeightIni( ) const;
	/// @brief 写入显示状态
	void writeShowIni( ) const;
public:
	MainWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	virtual QWidget * mouseToPoint( const QPoint &point );
	virtual QCursor setNormalCursorShape( );
	virtual QCursor setHCursorShape( );
	virtual QCursor setVCursorShape( );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	bool event( QEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
