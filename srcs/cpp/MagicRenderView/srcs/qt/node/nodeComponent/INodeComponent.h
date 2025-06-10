#ifndef INODECOMPONENT_H_H_HEAD__FILE__
#define INODECOMPONENT_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

class ITypeObject;
class INodeComponent : public QWidget {
	Q_OBJECT;
public:
	/// @brief 通道类型
	enum class Channel_Type {
		Normal_Default, // 默认
		Input_Read, // 输入
		Output_Write, // 输出
	};
protected:
	Channel_Type channelType;
public:
	INodeComponent( ) : INodeComponent( nullptr, Qt::WindowFlags( ) ) { }
	INodeComponent( QWidget *parent ) : INodeComponent( parent, Qt::WindowFlags( ) ) { }
	INodeComponent( QWidget *parent, Qt::WindowFlags f ) { channelType = Channel_Type::Normal_Default; }
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
	/// @brief 允许类型
	/// @param input_type 返回 true 表示允许输入通道
	/// @param output_type 返回 true 表示允许输出通道
	virtual void permissionChannel( bool &input_type, bool &output_type ) {
		input_type = true;
		output_type = true;
	}
	/// @brief 设置通道类型
	/// @param channel_type 通道类型
	/// @return 成功返回 true
	virtual bool setComponentChannel( const Channel_Type &channel_type ) {
		if( channelType == channel_type )
			return true;
		auto temp = channelType;
		channelType = channel_type;
		emit changeChannel( this, temp, channelType );
		return true;
	}
	/// @brief 获取通道类型
	/// @return 通道类型
	virtual Channel_Type getComponentChannel( ) const {
		return channelType;
	}
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
	/// @brief 当通道发生改变时，相应该信号
	/// @param component 消息指针
	/// @param old_channel_type 旧的通道类型
	/// @param new_channel_type 新通道类型
	void changeChannel( INodeComponent *component, Channel_Type old_channel_type, Channel_Type new_channel_type );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // INODECOMPONENT_H_H_HEAD__FILE__
