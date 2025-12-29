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
protected:
	using TRunBodyObj = Node ;
	using TRunBodyObjPtr = TRunBodyObj * ;
	using TRunBodyInfo = std::pair< TRunBodyObjPtr, size_t >;
	std::vector< TRunBodyObjPtr > beginNodeRefVector;
	std::vector< TRunBodyInfo > runVector;
	TRunBodyInfo *runArrayPtr;
	size_t runArrayCount;
	size_t runArrayIndex;
protected:
	virtual void appendBegin( TRunBodyObj *benin_node_ref_link_info );
	virtual void removeBegin( TRunBodyObj *benin_node_ref_link_info );
public:
	NodeRunInfo( QObject *parent );
	~NodeRunInfo( ) override;
	virtual bool hasNodeRefInRunVector( TRunBodyObj *check_node_ref );
	virtual bool builderRunInstance( );
	virtual bool runNextNode( );
	virtual bool runResidueNode( );
	virtual void clear( );
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
