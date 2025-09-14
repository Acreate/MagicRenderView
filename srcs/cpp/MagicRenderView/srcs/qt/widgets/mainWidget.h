#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

class QScrollArea;
class NodeItemWidget;
class QVBoxLayout;
class Application;
class MainWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 当前窗口的滚动页面
	QScrollArea *scrollArea;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 鼠标右键菜单
	QMenu *rightMouseBtnMenu;
	/// @brief 鼠标右击位置
	QPoint rightPos;
	/// @brief 窗口列表
	std_list< NodeItemWidget * > itemWidgets;
public:
	MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
