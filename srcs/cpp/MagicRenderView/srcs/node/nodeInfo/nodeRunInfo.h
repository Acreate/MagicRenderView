#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace NodeEnum {
	enum class ErrorType;
	enum class AdviseType;
}
class Node;
class NodeRefLinkInfo;
class SrackInfo;
class NodeRunInfo : public QObject {
	Q_OBJECT;
protected:
	using TRunBodyObj = NodeRefLinkInfo *;
	using TRunBodyInfo = std::pair< TRunBodyObj, size_t >;
	std::vector< TRunBodyObj > beginNodeRefVector;
	std::vector< TRunBodyInfo > runVector;
	TRunBodyInfo *runArrayPtr;
	size_t runArrayCount;
	size_t runArrayIndex;
public:
	NodeRunInfo( QObject *parent );
	~NodeRunInfo( ) override;
	virtual void appendBegin( NodeRefLinkInfo *benin_node_ref_link_info );
	virtual void removeBegin( NodeRefLinkInfo *benin_node_ref_link_info );
	virtual bool hasNodeRefInRunVector( NodeRefLinkInfo *check_node_ref );
	virtual bool builderRunInstance( );
	virtual bool runNextNode( );
	virtual bool runResidueNode( );
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node_port 释放对象指针
	/// @param srack_info 信号行
	void release_signal( NodeRunInfo *release_node_port, const SrackInfo &srack_info );
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
