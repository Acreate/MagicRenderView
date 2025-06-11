#ifndef INODECOMPONENT_H_H_HEAD__FILE__
#define INODECOMPONENT_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

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
	QString nodeComponentName;
public:
	INodeComponent( const QString &node_component_name, QWidget *parent, Qt::WindowFlags f ) {
		channelType = Channel_Type::Normal_Default;
		nodeComponentName = node_component_name;
		setAttribute( Qt::WA_InputMethodTransparent, true );
	}
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
	virtual const QString & getNodeComponentName( ) const { return nodeComponentName; }
	virtual void setNodeComponentName( const QString &node_component_name ) { nodeComponentName = node_component_name; }
	/// @brief 配置新的大小
	/// @param new_size 新大小
	virtual void setNewSize( const QSize &new_size );
	/// @brief 配置新的大小
	/// @param width 新宽度
	/// @param height 新高度
	virtual void setNewSize( const size_t &width, const size_t &height ) {
		setNewSize( QSize( width, height ) );
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
	/// @brief 测试变量是否允许修改该组件的值，该执行并不会更改该组件值
	/// @param object_ptr 测试的变量指针
	/// @return 允许被参数变量改变该组件则返回 true
	virtual bool tryLetChangeVar( const ITypeObject *object_ptr ) const {
		auto thisVarPtr = getVarObjectPtr( );
		if( thisVarPtr->metaObject( )->className( ) == object_ptr->metaObject( )->className( ) )
			return true;
		return false;
	}
	/// @brief 测试组件是否允许修改该组件的值，该执行并不会更改该组件值
	/// @brief 相同通道类型不能转换，如果不需要检测该配置，请使用 @code bool tryLetChangeVar( const ITypeObject *object_ptr ) const;  @endcode 
	/// @param component_object_ptr 测试的变量指针
	/// @return 允许被参数组件改变该组件则返回 true
	virtual bool tryLetChangeVar( const INodeComponent *component_object_ptr ) const {
		if( component_object_ptr->channelType == Channel_Type::Normal_Default || component_object_ptr->channelType == channelType )
			return false;
		return tryLetChangeVar( component_object_ptr->getVarObjectPtr( ) );
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
