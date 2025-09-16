#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QPainterPath>
#include <QWidget>

#include <alias/type_alias.h>

#include "../node/item/nodeItem.h"

class QScrollArea;
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
	/// @brief 按下时全局位置
	QPoint globalPressPos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalPressPoint;
	/// @brief 多用途位置信息
	QPoint modPoint;
	/// @brief 按下时全局位置
	QPoint globalReleasePos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalReleasePoint;
	/// @brief 鼠标移动时的坐标位置
	QPoint mouseMovePoint;
	/// @brief 节点链表
	std_list< NodeItem * > nodeItemList;
	/// @brief 选中的输入端口
	NodeInputPort *selectInputPort;
	/// @brief 选中的输出端口
	NodeOutputPort *selectOutputPort;
	/// @brief 选中的节点
	NodeItem *selectItem;
	/// @brief 激活的节点
	NodeItem *activeItem;
	/// @brief 拖拽项
	NodeItem *dragItem;
public:
	MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
