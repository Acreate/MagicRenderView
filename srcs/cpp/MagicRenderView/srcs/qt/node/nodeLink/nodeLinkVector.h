#ifndef NODELINKVECTOR_H_H_HEAD__FILE__
#define NODELINKVECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>
#include "./nodeLinkItem/nodeLinkItem.h"

class NodeLinkVector : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_mutex > mutex;
	std_shared_ptr< std_vector< NodeLinkItem > > nodeLinkItems;
	std_vector_pairt< INodeComponent *, INodeWidget * > nodeLinkStatus;
public:
	NodeLinkVector( );
	/// @brief 配置节点为可连接状态
	/// @param node_widget 节点
	/// @return 成功返回 true
	virtual bool usRegNodeLinkStatus( INodeWidget *node_widget );
	/// @brief 卸载节点可链接状态
	/// @param node_widget 节点
	/// @return 成功返回 true
	virtual bool unRegNodeLinkStatus( INodeWidget *node_widget );
	/// @brief 转换到标准序列对象，该方式为拷贝，返回对象不影响源对象
	/// @return 标准序列对象
	virtual std_vector< NodeLinkItem > toVector( ) const;
	/// @brief 使用标准序列对象重置该对象
	/// @param conver 源对象
	virtual void resetVector( const std_vector< NodeLinkItem > &conver ) const;
	/// @brief 检查是否存在该匹配项
	/// @param item 匹配项
	/// @return 存在返回 true
	virtual bool hasItem( const NodeLinkItem &item ) const;
	/// @brief 向序列末尾添加项
	/// @param item 新的项
	/// @return 成功返回 true
	virtual bool emplace_back( const NodeLinkItem &item );
	/// @brief 向序列末尾添加项，同 @code virtual bool emplace_back( const NodeLinkItem &item ); @endcode 
	/// @param item 新的项
	/// @return 成功返回 true
	virtual bool append( const NodeLinkItem &item ) {
		return emplace_back( item );
	}
	/// @brief 检测序列是否存在指定组件（同时检测输入与输出）
	/// @param unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasUnity( const INodeComponent *unity ) const;
	/// @brief 检测序列是否存在指定组件（同时检测输入与输出）
	/// @param unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasUnity( const INodeWidget *unity ) const;
	/// @brief 检测序列是否存在指定组件，只检测输入
	/// @param input_unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasInputUnity( const INodeComponent *input_unity ) const;
	/// @brief 检测序列是否存在指定组件，只检测输入
	/// @param input_unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasInputUnity( const INodeWidget *input_unity ) const;
	/// @brief 检测序列是否存在指定组件，只检测输出
	/// @param output_unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasOutputUnity( const INodeComponent *output_unity ) const;
	/// @brief 检测序列是否存在指定组件，只检测输出
	/// @param output_unity 检测的组件
	/// @return 不存在返回 0
	virtual int hasOutputUnity( const INodeWidget *output_unity ) const;
	/// @brief 删除第一个具备组件的输入项
	/// @param input_unity 检测的组件
	/// @return 不存在返回 0
	virtual int removeFirstInputItem( const INodeComponent *input_unity );
	/// @brief 删除第一个具备组件的输出项
	/// @param output_unity 检测的组件
	/// @return 不存在返回 0
	virtual int removeFirstOutputItem( const INodeComponent *output_unity );
	/// @brief 删除第一个同时具备组件的输出与输入的项
	/// @param output_unity 检测的输出项
	/// @param input_unity 检测的输入项
	/// @return 不存在返回 0
	virtual int removeFirstItem( const INodeComponent *output_unity, const INodeComponent *input_unity );
	/// @brief 获取存在指定输入的所有成员
	/// @param input_unity 匹配的指定输入
	/// @return 具备该输入条件的所有成员
	std_vector< NodeLinkItem > getOutLinkItems( const INodeComponent *input_unity ) const;
	/// @brief 获取存在指定输出的所有成员
	/// @param ouutput_unity 匹配的指定输出
	/// @return 具备该输出条件的所有成员
	std_vector< NodeLinkItem > getInLinkItems( const INodeComponent *ouutput_unity ) const;
	/// @brief 获取锁对象
	/// @return 锁
	virtual std_mutex * getMutex( ) const;
	/// @brief 锁
	/// @return 成功返回 true
	virtual bool lockMutex( ) const;
	/// @brief 解锁
	/// @return 成功返回 true
	virtual bool unMutex( ) const;
	/// @brief 获取序列大小，非线程安全
	/// @return 返回个数
	virtual size_t count( ) const;
	/// @brief 获取序列大小，非线程安全
	/// @return 返回个数
	virtual size_t size( ) const {
		return count( );
	}
	/// @brief 获取数据指针，非线程安全
	/// @return 失败返回 nullptr
	virtual NodeLinkItem * data( ) const;
	/// @brief 使用  begin( ) 进行遍历时，结束调用使用的成员函数
	virtual void end( ) const;
	/// @brief 获取开始迭代器与结束迭代器。
	/// 该调用会进行对象锁，如果需要结束迭代器并且进行解锁，应该使用 end()
	/// @return 
	virtual std_pairt< std_vector< NodeLinkItem >::iterator, std_vector< NodeLinkItem >::iterator > begin( ) const;
	virtual void clear( );
};

#endif // NODELINKVECTOR_H_H_HEAD__FILE__
