#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"

class ITypeObject;
class StringTypeObject;
class IFunctionDeclaration;
class NodeGraph;
class INodeComponent;
class INodeWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
public:
	/// @brief QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()
	/// @param function_declaration 函数信息
	/// @param parent 父节点，用于 qt 内存管理系统。
	/// @param f 窗口风格
	INodeWidget( const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f ) { }
	/// @brief 信号连接到指定窗口
	/// @param node_graph 响应信号的窗口
	virtual void connectNodeGraphWidget( NodeGraph *node_graph );
	virtual void call( ) {
		if( functionDeclaration )
			if( functionDeclaration.get( ) )
				functionDeclaration.get( )->call( );
	}
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclaration( ) const { return functionDeclaration; }
	virtual void setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration ) { functionDeclaration = function_declaration; }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
public:
Q_SIGNALS:
	/// @brief 选中窗口时候除法该信号
	/// @param event_node 触发节点
	/// @param select_component 当命中组件时，该指针不为 nullptr
	void selectNodeComponent( INodeWidget *event_node, QWidget *select_component );
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

#endif // INODEWIDGET_H_H_HEAD__FILE__
