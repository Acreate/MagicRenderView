#ifndef NODEGRAPH_H_H_HEAD__FILE__
#define NODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "alias/type_alias.h"
class ITypeObject;
class INodeWidget;
class INodeComponent;
class QLabel;
class NodeAddMenu;
class NodeGraph : public QWidget {
	Q_OBJECT;
private: // 私有类型
	enum class MouseEventType {
		Init, // 初始化
		Press, // 按下
		Release, // 释放
		Move,// 移动
	};
protected:
	/// @brief 节点添加菜单
	NodeAddMenu *nodeMenu;
	/// @brief 用于显示鼠标位置
	QLabel *mousePosLabel;
	/// @brief 当前鼠标状态
	MouseEventType mouseEventStatus;

	// 鼠标全局位置
	QPoint cursorPos;
	// 鼠标窗口位置
	QPoint currentMouseInWidgetPos;
	/// @brief 选中的控件
	QWidget *selectWidget;
	/// @brief 选中控件时，基于控件的相对偏移
	QPoint selectWidgetOffset;
public:
	NodeGraph( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeGraph( ) override;
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
public Q_SLOTS:
	void selectNodeComponentRelease( INodeWidget *event_node, QWidget *select_component, QPoint mouse_offset_pos );
	void selectNodeComponentPress( INodeWidget *event_node, QWidget *select_component, QPoint mouse_offset_pos );
	
	/// @brief 选中窗口时候除法该信号-鼠标释放触发
	/// @param event_node 触发节点
	/// @param select_component 当命中组件时，该指针不为 nullptr
	/// @param mouse_offset_pos 基于该节点的鼠标点击偏移
	void ActionNodeComponentRelease( INodeWidget *event_node, QWidget *select_component, QPoint mouse_offset_pos );
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
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
