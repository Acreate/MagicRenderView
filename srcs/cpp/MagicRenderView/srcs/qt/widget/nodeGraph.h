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
	/// @brief 选中的节点
	INodeWidget *selectNodeWidget;
	/// @brief 选中控件时，基于控件的相对偏移
	QPoint selectNodeWidgetOffset;

	/// @brief 选中的节点组件
	INodeComponent *selectNodeComponent;
	/// @brief 选择组件时的坐标位置
	QPoint selectNodeComponentPoint;
	/// @brief 节点链接线 call 列表
	std_vector<std_pairt<std_function<QPoint()>,std_function<QPoint()>>> nodeComponentLink;
	/// @brief 当前链接节点调用 call
	std_pairt<std_function<QPoint()>,std_function<QPoint()>> currentSelectLinkCall;
public:
	NodeGraph( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeGraph( ) override;
public:
	/// @brief 获取指定位置下的节点信息
	/// @param check_pos 位置
	/// @param result_node_widget 节点
	/// @param result_node_component 节点组件
	/// @return 存在节点返回 true
	virtual bool findPosNodeInfo( const QPoint &check_pos, INodeWidget **result_node_widget, INodeComponent **result_node_component );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
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
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
