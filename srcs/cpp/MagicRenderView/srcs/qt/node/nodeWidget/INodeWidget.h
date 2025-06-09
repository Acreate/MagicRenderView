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
	/// @brief 函数声明对象
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
	/// @brief 连接到该节点的节点
	std_shared_ptr< std_vector< const INodeWidget * > > connectNodeWidgets;
protected:
	/// @brief 链接到该节点
	/// @param target_node_widget 链接到该节点的对象指针
	virtual void linkThis( const INodeWidget *target_node_widget ) const {
		if( target_node_widget == nullptr )
			return;
		size_t count = connectNodeWidgets->size( );
		if( count > 0 ) {
			auto nodeWidget = connectNodeWidgets->data( );
			for( size_t index = 0; index < count; ++index )
				if( nodeWidget[ index ] == target_node_widget )
					return;
		}
		connectNodeWidgets->emplace_back( target_node_widget );
		connect( target_node_widget, &QObject::deleteLater, [this, target_node_widget]( ) {
			auto iterator = connectNodeWidgets->begin( );
			auto end = connectNodeWidgets->end( );
			for( ; iterator != end; ++iterator )
				if( iterator.operator*( ) == target_node_widget ) {
					connectNodeWidgets->erase( iterator );
					return;
				}
		} );
	}
	/// @brief 断开节点
	/// @param target_node_widget 断开该节点的对象指针
	virtual void unLinkThis( const INodeWidget *target_node_widget ) const {
		if( target_node_widget == nullptr )
			return;
		auto iterator = connectNodeWidgets->begin( );
		auto end = connectNodeWidgets->end( );
		for( ; iterator != end; ++iterator )
			if( iterator.operator*( ) == target_node_widget ) {
				disconnect( target_node_widget, &QObject::deleteLater, this, nullptr );
				connectNodeWidgets->erase( iterator );
				return;
			}
	}
public:
	/// @brief QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()
	/// @param function_declaration 函数信息
	/// @param parent 父节点，用于 qt 内存管理系统。
	/// @param f 窗口风格
	INodeWidget( const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ), connectNodeWidgets( new std_vector< const INodeWidget * > ) { }
	/// @brief 信号连接到指定窗口
	/// @param node_graph 响应信号的窗口
	virtual void connectNodeGraphWidget( NodeGraph *node_graph );
	virtual void call( ) const {
		if( functionDeclaration ) {
			size_t count = connectNodeWidgets->size( );
			if( count > 0 /* 链接到该节点的节点窗口 */ ) {
				auto nodeWidget = connectNodeWidgets->data( );
				for( size_t index = 0; index < count; ++index )
					nodeWidget[ index ]->call( );
			}
			functionDeclaration.get( )->call( );
		}
	}
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclaration( ) const { return functionDeclaration; }
	virtual void setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration ) { functionDeclaration = function_declaration; }
	/// @brief 获取返回值
	/// @return 返回值，不存在返回 nullptr
	virtual std_shared_ptr< ITypeObject > getResult( ) const = 0;
	/// @brief 获取包含的所有参数
	/// @return 参数列表，参数未被设置时，返回 nullptr
	virtual std_vector_unity_shared<ITypeObject> getParams() const = 0;
	/// @brief 设置参数
	/// @param params 参数列表
	/// @return 成功被设置的参数列表，设置失败参数则不在该返回
	virtual std_vector_unity_shared<ITypeObject> setParams(const std_vector_unity_shared<ITypeObject>& params) const = 0;
	/// @brief 设置指定位置的参数
	/// @param param 参数
	/// @param param_index 设置的参数位置
	/// @return 设置成功返回 true
	virtual bool setParam(const std_shared_ptr<ITypeObject>& param, size_t param_index) const = 0;
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
public:
Q_SIGNALS:
	/// @brief 选中窗口时候除法该信号-鼠标释放触发
	/// @param event_node 触发节点
	/// @param select_component 当命中组件时，该指针不为 nullptr
	/// @param mouse_offset_pos 基于该节点的鼠标点击偏移
	void selectNodeComponentRelease( INodeWidget *event_node, QWidget *select_component, QPoint mouse_offset_pos );
	/// @brief 选中窗口时候除法该信号-鼠标按下触发
	/// @param event_node 触发节点
	/// @param select_component 当命中组件时，该指针不为 nullptr
	/// @param mouse_offset_pos 基于该节点的鼠标点击偏移
	void selectNodeComponentPress( INodeWidget *event_node, QWidget *select_component, QPoint mouse_offset_pos );
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
