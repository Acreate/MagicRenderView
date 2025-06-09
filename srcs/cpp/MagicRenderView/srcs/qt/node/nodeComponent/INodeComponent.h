#ifndef INODECOMPONENT_H_H_HEAD__FILE__
#define INODECOMPONENT_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

class ITypeObject;
class INodeComponent : public QWidget {
	Q_OBJECT;
public:
	INodeComponent( ) : INodeComponent( nullptr, Qt::WindowFlags( ) ) { }
	INodeComponent( QWidget *parent ) : INodeComponent( parent, Qt::WindowFlags( ) ) { }
	INodeComponent( QWidget *parent, Qt::WindowFlags f ) { }
public:
	/// @brief 获取值
	/// @return 值指针对象
	virtual const std_shared_ptr< ITypeObject > getVarObject( ) const =0;
	/// @brief 获取值
	/// @return 值指针
	virtual const ITypeObject * getVarObjectPtr( ) const =0;
	/// @brief 设置新值
	/// @param new_var 新值 
	/// @return 成功返回 true
	virtual bool setVar( const std_shared_ptr< ITypeObject > &new_var ) const = 0;
	/// @brief 设置新值
	/// @param new_var 新值 
	/// @return 成功返回 true
	virtual bool setVar( const ITypeObject &new_var ) const = 0;
	/// @brief 重置值
	/// @return 成功返回 true
	virtual bool resetOrg( ) = 0;
public:
	/// @brief 配置新的大小
	/// @param new_size 新大小
	virtual void setNewSize( const QSize &new_size );
	/// @brief 配置新的大小
	/// @param width 新宽度
	/// @param height 新高度
	virtual void setNewSize( const size_t &width, const size_t &height ) {
		setNewSize( QSize( width, height ) );
	}
Q_SIGNALS:
	/// @brief 控件大小被改变
	void changeSize( QSize new_size );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // INODECOMPONENT_H_H_HEAD__FILE__
