﻿#ifndef NODEGRAPH_H_H_HEAD__FILE__
#define NODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../node/nodeLink/nodeLinkItem/nodeLinkItem.h"

#include "../serialize/ISerialize.h"

#include "alias/type_alias.h"

class NodeLinkVector;
class MainWindow;
class ITypeObject;
class INodeWidget;
class INodeComponent;
class QLabel;
class NodeAddMenu;
class NodeGraph : public QWidget, public ISerialize {
	Q_OBJECT;
public: // 类型
	enum class MouseEventType {
		Init, // 初始化
		Press, // 按下
		Release, // 释放
		Move,// 移动
	};
protected:
	/// @brief 主要窗口
	MainWindow *mainWindow;
	/// @brief 节点添加菜单
	NodeAddMenu *nodeMenu;
	/// @brief 用于显示鼠标位置
	QLabel *mousePosLabel;
	/// @brief 点击位置的绘制一半大小
	QSize mousePosLabelHalfSize;
	/// @brief 当前鼠标状态
	MouseEventType mouseEventStatus;
	// 鼠标全局位置
	QPoint cursorPos;
	// 鼠标窗口位置
	QPoint currentMouseInWidgetPos;
	/// @brief 所有节点
	std_vector< INodeWidget * > nodeWidgets;
	/// @brief 激活节点
	INodeWidget *activeNodeWidget;
	/// @brief 选中的节点
	INodeWidget *selectNodeWidget;
	/// @brief 选中控件时，基于控件的相对偏移
	QPoint selectNodeWidgetOffset;
	/// @brief 选中的节点组件
	INodeComponent *selectNodeComponent;
	/// @brief 选择组件时的坐标位置
	QPoint selectNodeComponentPoint;
	/// @brief 节点组件的连接
	std_shared_ptr< NodeLinkVector > nodeLinkItems;
	/// @brief 组件节点锁
	std_shared_ptr< std_mutex > nodeWidgetIDMutex;
	/// @brief 建议请求组件节点锁
	std_shared_ptr< std_mutex > nodeWidgetAdviseIDMutex;
	/// @brief 存储节点id
	std_shared_ptr< std_vector_pairt< INodeWidget *, size_t > > nodeWidgetID;
public:
	NodeGraph( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeGraph( ) override;
public:
	/// @brief 获取当前被激活的节点
	/// @return nullptr 表示不存在
	virtual INodeWidget * getActiveNodeWidget( ) const { return activeNodeWidget; }
	/// @brief 获取指定位置下的节点信息
	/// @param check_pos 位置
	/// @param result_node_widget 节点
	/// @param result_node_component 节点组件
	/// @return 存在节点返回 true
	virtual bool findPosNodeInfo( const QPoint &check_pos, INodeWidget **result_node_widget, INodeComponent **result_node_component );
	/// @brief 更新渲染窗口的大小
	virtual void updateMinSize( );
	/// @brief 实现序列化之后，调用该函数
	/// @param over_widget_list 实现反序列化的节点
	/// @param new_link_items_vector 新的连接列表
	/// @return 成功返回 true
	virtual bool overSerializeToObjectData( const std_vector_pairt< INodeWidget *, size_t > &over_widget_list, const std_vector< NodeLinkItem > &new_link_items_vector );
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
	size_t getNodeWidgetID( const INodeWidget *node_widget ) const;
	INodeWidget * getNodeWidgetFromID( const size_t &id ) const;
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual void setMainWindow( MainWindow *const main_window ) { mainWindow = main_window; }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
protected:
	size_t registerID( INodeWidget *request_ui_ptr );
	size_t registerID( INodeWidget *request_ui_ptr, size_t advise_id );
	size_t removeId( INodeWidget *request_ui_ptr );
public Q_SLOTS:
	/// @brief 执行错误时，产生该消息
	/// @param send_obj_ptr 信号对象
	/// @param msg 错误消息
	/// @param error_code 错误代码
	/// @param error_line 错误行
	void error( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &msg, size_t error_code, size_t error_line );
	/// @brief 执行完毕调用该函数
	/// @param send_obj_ptr 信号对象
	/// @param result_type_object 返回对象
	/// @param return_code 返回代码
	/// @param over_line 执行完成的行
	void finish( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &result_type_object, size_t return_code, size_t over_line );
	/// @brief 请求id
	/// @param request_node_widget_ptr 请求节点
	void requestNodeWidgetID( INodeWidget *request_node_widget_ptr );
	/// @brief 请求id
	/// @param request_node_widget_ptr 请求节点
	/// @param advise_id 建议 id
	void requestNodeWidgetAdviseID( INodeWidget *request_node_widget_ptr, size_t advise_id );
	/// @brief 请求id
	/// @param request_node_widget_ptr 请求节点
	void destoryNodeWidgetID( INodeWidget *request_node_widget_ptr );
Q_SIGNALS:
	/// @brief 激活节点时，触发该信号
	/// @param node_graph 信号发送者
	/// @param now_select_active_node_widget 激活的节点
	/// @param old_select_active_node_widget 旧的激活节点
	void selectActiveNodeWidget( NodeGraph *node_graph, INodeWidget *now_select_active_node_widget, INodeWidget *old_select_active_node_widget );
	/// @brief 激活节点时，触发该信号
	/// @param node_graph 信号发送者
	/// @param new_active_node_widget 新增节点
	/// @param node_widgets 节点列表
	void generateNodeWidget( NodeGraph *node_graph, INodeWidget *new_active_node_widget, const std_vector< INodeWidget * > &node_widgets );
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
