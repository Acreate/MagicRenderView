#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QPainterPath>
#include <QWidget>
#include <qdatetime.h>

#include <alias/type_alias.h>

#include "../node/item/nodeItem.h"

#include "../varType/I_Type.h"

class NodePortLinkInfo;
class NodeDirector;
class NodeInputPort;
class VarGenerate;
class I_Var;
class NodeOutputPort;
class NodeItem;
class NodePort;
class QScrollArea;
class QVBoxLayout;
class Application;
class MainWidget : public QWidget {

	Q_OBJECT;
private:
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
protected:
	/// @brief 当前窗口的滚动页面
	QScrollArea *scrollArea;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 支持序列化
	VarGenerate *varGenerate;
	/// @brief 节点导演
	NodeDirector *nodeDirector;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 用于创建节点的菜单-鼠标右键对应空白即可弹出
	QMenu *rightMouseBtnCreateNodeItemMenu;
	/// @brief 多用途位置信息
	QPoint modPoint;
	/// @brief 鼠标移动时的坐标位置
	QPoint mouseMovePoint;
	/// @brief 记录点击时间点
	QDateTime sigClickDateTime;
	/// @brief 点击类型
	NodeItem::Click_Type clickNodeItemType;
	/// @brief 第一次左键
	NodeItem *leftFirstSelectItem;
	/// @brief 第二次左键
	NodeItem *leftScondSelectItem;
	/// @brief 第一次左键
	NodePort *leftFirstSelectPort;
	/// @brief 第二次左键
	NodePort *leftScondSelecttPort;
	/// @brief 鼠标右键选中项
	NodeItem *rightMouseBtnSelectItem;
	/// @brief 鼠标右键选中节点
	NodePort *rightMouseBtnSelectPort;
	/// @brief 用于删除当前选中节点的菜单
	QMenu *removeSelectNodeItemMenu;
	/// @brief 用于右键删除节点时使用的信息列表
	std_vector<NodeOutputPort*> rightMenuRemoveInfo;
public:
	MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	/// @brief 窗口滚动到指定节点位置-大小不足时进行窗口扩充
	/// @param targetItemNode 目标节点
	virtual void ensureVisibleToItemNode( const NodeItem *targetItemNode );
protected:
	virtual void linkNodePortEvent( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	virtual void unlinkNodePortEvent( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
