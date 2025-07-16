#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

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
	/// @brief 存储子组件ID
	std_vector_pairt< INodeComponent *, size_t > componentID;
	/// @brief 组件ID读取锁
	std_shared_ptr< std_mutex > componentIDMutex;
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
	virtual void call( ) const;
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
	/// @brief 获取子组件在当前节点中的 ID 编号
	/// @param node_component 组件指针
	/// @return 子组件ID
	virtual size_t getChildNodeCompoentID( const INodeComponent *node_component ) const;
	/// @brief 根据 ID 获取组件
	/// @param id 匹配 id
	/// @return 组件，不存在返回 nullptr
	virtual INodeComponent * getComponetFromID( const size_t &id ) const;
	/// @brief 获取组件映射 ID
	/// @return 组件ID列表
	virtual std_vector_pairt< INodeComponent *, size_t > getComponentID( ) const {
		std_lock_grad_mutex lockGradMutex( *componentIDMutex );
		return componentID;
	}
	virtual std_vector< INodeComponent * > getNodeComponents( ) const {
		std_vector< INodeComponent * > result;
		std_lock_grad_mutex lockGradMutex( *componentIDMutex );
		size_t count = componentID.size( );
		auto pair = componentID.data( );
		for( size_t index = 0; index < count; ++index )
			result.emplace_back( pair[ index ].first );
		return result;
	}
	~INodeWidget( ) override;
public Q_SLOTS:
	/// @brief 节点注册id完成
	/// @param id 注册的id
	virtual void registerIDFinish( size_t id );
protected:
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	/// @brief 该对象删除时触发信号
	void thisNodeWidgetRemove( INodeWidget *send_obj_ptr );
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
	/// @brief 替换链接时触发该信号
	/// @param old_output 旧连接到该组件的输出
	/// @param new_output 新连接到该组件的输出
	/// @param current_input 接受输出的输入组件
	void replaceLink( INodeComponent *old_output, INodeComponent *new_output, INodeComponent *current_input );
	/// @brief 追加链接时触发该信号
	/// @param old_output_vector 旧的链接输出列表
	/// @param append_new_output 追加新的输出链接
	/// @param current_input 接受输出的输入组件
	void appendLink( std_vector< INodeComponent * > old_output_vector, INodeComponent *append_new_output, INodeComponent *current_input );
	/// @brief 断开链接时触发该信号
	/// @param disconnect_output 断开的输出链接组件
	/// @param current_input 断开的输入链接组件
	void disconnectLink( INodeComponent *disconnect_output, INodeComponent *current_input );
	/// @brief 组件值被改变时触发该信号
	/// @param value_component 值被改变的组件
	/// @param old_var_value 旧的变量值
	/// @param new_var_value 新的变量值
	void changedComponentValue( INodeComponent *value_component, const std_shared_ptr< ITypeObject > &old_var_value, const std_shared_ptr< ITypeObject > &new_var_value );
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
