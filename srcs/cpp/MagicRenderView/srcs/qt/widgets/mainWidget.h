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
	/// @brief 用于创建节点的菜单-鼠标右键对应空白即可弹出
	QMenu *rightMouseBtnCreateNodeItemMenu;
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
	/// @brief 鼠标左键选中的输入端口
	NodeInputPort *leftMouseBtnSelectInputPort;
	/// @brief 鼠标左键选中的输出端口
	NodeOutputPort *leftMouseBtnSelectOutputPort;
	/// @brief 鼠标左键选中的节点
	NodeItem *leftMouseBtnSelectItem;
	/// @brief 窗口当时激活的节点
	NodeItem *renderWidgetActiveItem;
	/// @brief 鼠标左键拖拽项
	NodeItem *leftMouseBtnDragItem;
	/// @brief 鼠标右键选中项
	NodeItem *rightMouseBtnSelectItem;
	/// @brief 鼠标右键选中节点
	NodeInputPort *rightMouseBtnSelectPort;
	/// @brief 用于操作删除输出接口的菜单-鼠标右键命中输入接口是弹出
	QMenu *rightMouseBtnRemoveOutPortMenu;
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
