#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../enums/nodeEnum.h"

class Application;
namespace NodeEnum {
	enum class ErrorType;
	enum class AdviseType;
}
class Node;
class NodeDirector;
class SrackInfo;
class NodeRunInfo : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
protected:
	using TRunBodyObj = Node;
	using TRunBodyObjPtr = TRunBodyObj *;
	std::vector< TRunBodyObjPtr > builderNodeVector;
	std::vector< TRunBodyObjPtr > runNodeVector;
	size_t builderNodeCount;
	size_t builderNodeIndex;
	TRunBodyObjPtr *builderNodeArrayPtr;
	size_t runNodeCount;
	size_t runNodeIndex;
	TRunBodyObjPtr *runNodeArrayPtr;
	TRunBodyObjPtr errorObj;
	bool isRunStop;
protected:
	virtual void appendBuilderNode( TRunBodyObj **append_node_array_ptr, const size_t &append_node_array_count );
	virtual void appendBuilderNode( std::vector< TRunBodyObj * > &append_node_vector ) {
		appendBuilderNode( append_node_vector.data( ), append_node_vector.size( ) );
	}
	virtual void appendBuilderNode( TRunBodyObj *append_node_unity );
	virtual void removeBuilderNode( TRunBodyObj *append_node_unity );
	/// @brief 编译实例
	/// @return 失败返回 false
	virtual bool builderRunInstance( );
	/// @brief 编译实例引用
	/// @return 失败返回 false
	virtual bool builderRunInstanceRef( );

public:
	NodeRunInfo( );
	~NodeRunInfo( ) override;
	/// @brief 检查是否存在指定节点
	/// @param check_node_ref 检查节点
	/// @return 不存在返回 false
	virtual bool hasNodeRefInRunVector( TRunBodyObj *check_node_ref );
	/// @brief 运行下一个
	/// @return 成功返回 true
	virtual bool runNextNode( );
	/// @brief 运行剩余
	/// @return 成功返回 true
	virtual bool runResidueNode( );
	/// @brief 停止运行
	/// @return 成功返回 true
	virtual bool runStopNode( );
	/// @brief 清理所有
	virtual void clear( );
	/// @brief 获取错误节点
	/// @return 如果存在，返回错误节点
	virtual TRunBodyObj * getErrorObj( ) const {
		return errorObj;
	}
	virtual size_t getBeginNodeCount( ) const { return builderNodeCount; }
	virtual TRunBodyObjPtr * getBeginNodeData( ) const { return builderNodeArrayPtr; }
	virtual size_t getRunNodeCount( ) const { return runNodeCount; }
	virtual TRunBodyObjPtr * getRunNodeData( ) const { return runNodeArrayPtr; }
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_obj_ptr 释放对象指针
	/// @param srack_info 信号行
	void release_signal( NodeRunInfo *release_obj_ptr, const SrackInfo &srack_info );
	/// @brief 清理对象产生信号
	/// @param clear_obj 清理对象
	/// @param srack_info 信号堆栈
	void clear_signal( NodeRunInfo *clear_obj, const SrackInfo &srack_info );
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
