#ifndef NODERUNLINK_H_H_HEAD__FILE__
#define NODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLinkData.h"

class NodeRunInfo;
class Node;
class NodeRunLink : public NodeRunLinkData {
	Q_OBJECT;
	friend class NodeRunInfo;
public:
	~NodeRunLink( ) override;
protected:
	NodeRunLink( Node *const init_node_ptr );
	/// @brief 链接节点
	/// @return 失败返回 false
	virtual bool builder( ) = 0;
	/// @brief 获取下一个运行节点
	/// @param result_next_node_ptr 下一个运行节点
	/// @return 失败返回 false
	virtual bool getNextRunNode( Node *&result_next_node_ptr ) = 0;
	/// @brief 运行节点
	/// @param run_node_ptr 运行的节点
	/// @param run_time 运行时间
	/// @param run_frame 运行帧
	/// @return 成功返回 true
	virtual bool runRunNode( Node *run_node_ptr, const QDateTime &run_time, size_t run_frame );
	bool adviseRunNode( const Node *const node ) const override;
	const std::vector< Node * > & getAdviseNodeVector( ) const override;
	Node * getBeforeNode( ) const override;
	Node * getCurrentNode( ) const override;
	const std::vector< Node * > & getLinkNodeVector( ) const override;
	const std::vector< Node * > & getOverRunNodeVector( ) const override;
	Node * getStartNode( ) const override;
	bool isOver( ) const override;
	bool isReady( ) const override;
	bool linkHasNode( const Node *const check_node_ptr ) const override;
};

#endif // NODERUNLINK_H_H_HEAD__FILE__
