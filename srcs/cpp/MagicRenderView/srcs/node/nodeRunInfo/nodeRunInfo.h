#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

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
	template< typename TNode >
	class ExtendVector {
		std::vector< TNode * > nodeVector;
		size_t index;
		size_t count;
	public:

	};
protected:
	using TRunBodyObj = Node;
	using TRunBodyObjPtr = TRunBodyObj *;
	std::vector< TRunBodyObjPtr > beginNodeVector;
	std::vector< TRunBodyObjPtr > runNodeVector;
	size_t beginNodeCount;
	size_t beginNodeIndex;
	TRunBodyObjPtr *beginNodeArrayPtr;
	size_t runNodeCount;
	size_t runNodeIndex;
	TRunBodyObjPtr *runNodeArrayPtr;
	TRunBodyObjPtr errorObj;
protected:
	virtual void appendBegin( TRunBodyObj *benin_node_ref_link_info );
	virtual void removeBegin( TRunBodyObj *benin_node_ref_link_info );
	/// @brief 编译实例
	/// @return 失败返回 false
	virtual bool builderRunInstance( );
public:
	NodeRunInfo( QObject *parent );
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
	/// @brief 清理所有
	virtual void clear( );
	/// @brief 获取错误节点
	/// @return 如果存在，返回错误节点
	virtual TRunBodyObj * getErrorObj( ) const {
		return errorObj;
	}
	virtual size_t getBeginNodeCount( ) const { return beginNodeCount; }
	virtual TRunBodyObjPtr * getBeginNodeData( ) const { return beginNodeArrayPtr; }
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
