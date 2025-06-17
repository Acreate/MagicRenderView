#ifndef NODEGRAPH_H_H_HEAD__FILE__
#define NODEGRAPH_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "alias/type_alias.h"

#include "qt/node/nodeLink/nodeLinkItem.h"
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
	/// @brief 所有节点
	std_vector< INodeWidget * > nodeWidgets;
	/// @brief 选中的节点
	INodeWidget *selectNodeWidget;
	/// @brief 选中控件时，基于控件的相对偏移
	QPoint selectNodeWidgetOffset;

	/// @brief 选中的节点组件
	INodeComponent *selectNodeComponent;
	/// @brief 选择组件时的坐标位置
	QPoint selectNodeComponentPoint;
	/// @brief 节点组件的连接
	std_vector< NodeLinkItem > nodeLinkItems;
	/// @brief 组件id锁
	std_mutex nodeComponentIDMutex;
	/// @brief 组件节点锁
	std_mutex nodeWidgetIDMutex;
	/// @brief 存储组件id
	std_vector_pairt< INodeComponent *, size_t > nodeComponentID;
	/// @brief 存储节点id
	std_vector_pairt< INodeWidget *, size_t > nodeWidgetID;
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
	/// @brief 更新渲染窗口的大小
	virtual void updateMinSize( );
	/// @brief 检查连接列表当中是否存在组件
	/// @param unity 检查组件
	/// @return 返回 1 表示存在输入，返回 -1 表示存在输出，返回 0 表示不存在
	virtual int linkHasUnity( const INodeComponent *unity ) const;
	/// @brief 检查连接列表当中是否存在节点
	/// @param unity 检查节点
	/// @return 返回 1 表示存在输入，返回 -1 表示存在输出，返回 0 表示不存在
	virtual int linkHasUnity( const INodeWidget *unity ) const;
	/// @brief 检查连接列表当中是否存在输入组件
	/// @param input_unity 检查组件
	/// @return 返回 0 表示不存在
	virtual int linkHasInputUnity( const INodeComponent *input_unity ) const;
	/// @brief 检查连接列表当中是否存在输入节点
	/// @param input_unity 检查节点
	/// @return 返回 0 表示不存在
	virtual int linkHasInputUnity( const INodeWidget *input_unity ) const;
	/// @brief 检查连接列表当中是否存在输出组件
	/// @param output_unity 检查组件
	/// @return 返回 0 表示不存在
	virtual int linkHasOutputUnity( const INodeComponent *output_unity ) const;
	/// @brief 检查连接列表当中是否存在输出节点
	/// @param output_unity 检查节点
	/// @return 返回 1 表示存在输入，返回 -1 表示存在输出，返回 0 表示不存在
	virtual int linkHasOutputUnity( const INodeWidget *output_unity ) const;
	/// @brief 删除第一个链接的输入组件
	/// @param input_unity 输入组件
	/// @return 成功返回 1
	virtual int linkRemoveFirstInputItem( const INodeComponent *input_unity );
	/// @brief 删除第一个链接配对的输入组件
	/// @param output_unity 输出组件
	/// @param input_unity 输入组件
	/// @return 成功返回 1
	virtual int linkRemoveFirstInputItem( const INodeComponent *output_unity, const INodeComponent *input_unity );
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
protected:
	size_t randomId( INodeComponent *request_ui_ptr );
	size_t randomId( INodeWidget *request_ui_ptr );
	size_t removeId( INodeComponent *request_ui_ptr );
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
	/// @param request_node_component_ptr 请求组件
	void requestNodeComponentID( INodeComponent *request_node_component_ptr );
	/// @brief 请求id
	/// @param request_node_widget_ptr 请求节点
	void destoryNodeWidgetID( INodeWidget *request_node_widget_ptr );
	/// @brief 请求id
	/// @param request_node_component_ptr 请求组件
	void destoryNodeComponentID( INodeComponent *request_node_component_ptr );
};

#endif // NODEGRAPH_H_H_HEAD__FILE__
