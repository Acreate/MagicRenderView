#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/serialize/ISerialize.h"

class INodeStack;
class NodeInputLineText;
class QLabel;
class QVBoxLayout;
class ITypeObject;
class StringTypeObject;
class IFunctionDeclaration;
class NodeGraph;
class INodeComponent;
class INodeWidget : public QWidget {
	Q_OBJECT;
public:
	friend class NodeGraph;
protected:
	/// @brief 函数声明对象
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
	/// @brief 节点窗口名称
	std_vector< QString > nodeWidgetNames;
	/// @brief 生成该节点的对象
	std_shared_ptr< INodeStack > nodeStack;
	/// @brief 节点工厂生成函数
	std_function< std_shared_ptr< INodeStack >( ) > getStackFunction;
protected: // ui
	/// @brief 标题
	QLabel *title;
	/// @brief 布局
	QVBoxLayout *mainBoxLayout;
public:
	/// @brief QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()
	/// @param get_stack_function 节点生成函数
	/// @param node_widget_name_s 节点名称
	/// @param function_declaration 函数信息
	/// @param parent 父节点，用于 qt 内存管理系统。
	/// @param f 窗口风格
	INodeWidget( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function, const std_vector< QString > &node_widget_name_s, const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f );
	/// @brief 信号连接到指定窗口
	/// @param node_graph 响应信号的窗口
	virtual void connectNodeGraphWidget( NodeGraph *node_graph );
	virtual void call( ) const {
		if( functionDeclaration ) 
			functionDeclaration.get( )->call( );
	}
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclaration( ) const { return functionDeclaration; }
	virtual void setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration ) { functionDeclaration = function_declaration; }
	/// @brief 获取返回值
	/// @return 返回值，不存在返回 nullptr
	virtual std_shared_ptr< ITypeObject > getResult( ) const = 0;
	/// @brief 获取包含的所有参数
	/// @return 参数列表，参数未被设置时，返回 nullptr
	virtual std_vector_unity_shared< ITypeObject > getParams( ) const = 0;
	/// @brief 设置参数
	/// @param params 参数列表
	/// @return 成功被设置的参数列表，设置失败参数则不在该返回
	virtual std_vector_unity_shared< ITypeObject > setParams( const std_vector_unity_shared< ITypeObject > &params ) const = 0;
	/// @brief 设置指定位置的参数
	/// @param param 参数
	/// @param param_index 设置的参数位置
	/// @return 设置成功返回 true
	virtual bool setParam( const std_shared_ptr< ITypeObject > &param, size_t param_index ) const = 0;
	virtual std_vector< QString > getNodeNames( ) const {
		return nodeWidgetNames;
	}
	/// @brief 获取位置下的组件
	/// @param pos 位置
	/// @return 组件
	virtual INodeComponent * getPosNodeComponent( const QPoint &pos ) const;
	/// @brief 获取组件可链接位置
	/// @param component 组件
	/// @param resulut_pos 位置
	/// @return 失败返回 false
	virtual bool getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const;
	const std_shared_ptr< INodeStack > & getNodeStack( ) const { return nodeStack; }
	const std_function< std_shared_ptr< INodeStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
	virtual void setNodoTitle( const QString &titile );
	virtual QString getNodeTitle( ) const;
	virtual size_t getID( ) const;
public Q_SLOTS:
	/// @brief 节点注册id完成
	/// @param id 注册的id
	virtual void registerIDFinish( size_t id );
protected:
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
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
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
