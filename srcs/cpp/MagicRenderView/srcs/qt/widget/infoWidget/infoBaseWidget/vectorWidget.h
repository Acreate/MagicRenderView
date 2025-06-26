#ifndef VECTORWIDGET_H_H_HEAD__FILE__
#define VECTORWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"



class VectorTypeObject;
class VectorWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< VectorWidget > thisConverObject;
	std_shared_ptr< VectorTypeObject > value;
public:
	VectorWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );

	/// @brief 获取下标值
	/// @param index 下标
	/// @return 值，失败返回 NullTypeObject
	virtual std_shared_ptr< ITypeObject > atIndex( const size_t &index ) const;
	/// @brief 获取下标值
	/// @param index 下标
	/// @return 值，失败返回 NullTypeObject
	virtual std_shared_ptr< ITypeObject > operator[]( const size_t &index ) const {
		return atIndex( index );
	}
	/// @brief 配置序列
	/// @param vector 配置的序列
	virtual void setVector( const std_vector< std_shared_ptr< ITypeObject > > &vector );
	virtual bool append( const std_shared_ptr< ITypeObject > &type_object );
	/// @brief 返回序列
	/// @return 返回的序列
	virtual std_vector< std_shared_ptr< ITypeObject > > getVector( ) const;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;
};

#endif // VECTORWIDGET_H_H_HEAD__FILE__
