#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

class ItemWidget;
class QVBoxLayout;
class Application;
class MainWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 应用实例
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 鼠标右键菜单
	QMenu *rightMouseBtnMenu;
	/// @brief 鼠标右击位置
	QPoint rightPos;
	/// @brief 窗口列表
	std_list< ItemWidget * > itemWidgets;
public:
	MainWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	virtual void clickItemWidget( ItemWidget *click_item_widget );
	virtual void doubleClickItemWidget( ItemWidget *double_click_item_widget );
	virtual void createNewItemWidget( bool flage );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void s_signals_createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect );
	void s_signals_clickItemWidget( ItemWidget *click_item_widget );
	void s_signals_doubleClickItemWidget( ItemWidget *double_click_item_widget );
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
