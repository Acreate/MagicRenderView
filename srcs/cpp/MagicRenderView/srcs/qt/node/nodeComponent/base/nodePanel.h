#ifndef NODEPANEL_H_H_HEAD__FILE__
#define NODEPANEL_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeComponent/INodeComponent.h"

class QHBoxLayout;
class QVBoxLayout;
class NodePanel : public INodeComponent {
	Q_OBJECT
protected: // ui
	/// @brief 左窗口
	QWidget *leftWidget;
	/// @brief 右窗口
	QWidget *rightWidget;
	/// @brief 左侧布局列表
	QVBoxLayout *leftVectorBoxLayout;
	/// @brief 右侧布局列表
	QVBoxLayout *rightVectorBoxLayout;
	/// @brief 主体布局列表
	QHBoxLayout *mainLayout;
public:
	/// @brief 增加输入选项
	/// @param input_component 输入选项
	/// @return 成功返回 true
	virtual bool appendInput( INodeComponent *input_component );
	/// @brief 删除输入选项
	/// @param output_component 删除组件
	/// @return 成功返回 true
	virtual bool removeInputItem( INodeComponent *output_component );
	/// @brief 删除指定下表的输入选项
	/// @param index 删除下标
	/// @return 成功返回 true
	virtual QWidget * removeInputItem( size_t index );
	/// @brief 获取指定下标的输入项
	/// @param index 下标
	/// @return 失败返回 nullptr
	virtual QWidget * getInputItem( size_t index ) const;
	/// @brief 增加输出选项
	/// @param output_component 输出选项
	/// @return 成功返回 true
	virtual bool appendOutput( INodeComponent *output_component );
	/// @brief 删除输入选项
	/// @param output_component 删除组件
	/// @return 成功返回 true
	virtual bool removeOutputItem( INodeComponent *output_component );
	/// @brief 删除指定下表的输入选项
	/// @param index 删除下标
	/// @return 成功返回 true
	virtual QWidget * removeOutputItem( size_t index );
	/// @brief 获取指定下标的输入项
	/// @param index 下标
	/// @return 失败返回 nullptr
	virtual QWidget * getOutputItem( size_t index ) const;
protected:
	void updateSize( );
	void childComponentChangeChannel( INodeComponent *component, Channel_Type old_channel_type, Channel_Type new_channel_type );
public:
	NodePanel( const QString &node_component_name, QWidget *parent, Qt::WindowFlags f );
	NodePanel( const QString &node_component_name, QWidget *parent ): NodePanel( node_component_name, parent, Qt::WindowFlags( ) ) {
	}
	const std_shared_ptr< ITypeObject > getVarObject( ) const override {
		return nullptr;
	}
	const ITypeObject * getVarObjectPtr( ) const override {
		return nullptr;
	}
	bool setVar( const std_shared_ptr< ITypeObject > &new_var ) const override {
		return false;
	}
	bool setVar( const ITypeObject &new_var ) const override {
		return false;
	}
	bool resetOrg( ) override {
		return true;
	}
	INodeComponent * getPosNodeComponent( const QPoint &pos ) const override;
	bool getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const override;
protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEPANEL_H_H_HEAD__FILE__
