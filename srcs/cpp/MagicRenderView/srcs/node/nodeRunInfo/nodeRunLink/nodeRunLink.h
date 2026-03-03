#ifndef NODERUNLINK_H_H_HEAD__FILE__
#define NODERUNLINK_H_H_HEAD__FILE__
#include <QObject>

class NodeRunLinkData;
class NodeRunInfo;
class Node;
namespace NodeRunLinkTools {
	class Get;
}
class NodeRunLink : public QObject {
	Q_OBJECT;
	friend class NodeRunInfo;
public:
	~NodeRunLink( ) override;
protected:
	NodeRunLinkData *nodeRunLinkData;
	NodeRunLinkTools::Get *get;
protected:
	NodeRunLink( Node *const init_node_ptr );
	/// @brief 链接节点
	/// @return 失败返回 false
	virtual bool builder( ) = 0;
	/// @brief 获取下一个运行节点
	/// @param over_run_node_vector 运行完毕列表
	/// @param result_next_node_ptr 下一个运行节点
	/// @return 失败返回 false
	virtual bool getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr );
	/// @brief 运行节点
	/// @param run_node_ptr 运行的节点
	/// @param run_time 运行时间
	/// @param run_frame 运行帧
	/// @return 成功返回 true
	virtual bool runRunNode( Node *run_node_ptr, const QDateTime &run_time, size_t run_frame );
	/// @brief 获取节点的建议列表
	/// @param get_advise_node_ptr 获取的节点
	/// @param result_advise_node_vector 建议运行列表
	/// @param ndoe_run_start_data_time 当前运行时间
	/// @param current_frame 当前帧
	/// @return 失败返回 false
	virtual bool getNodeRunAdviseNodeVector( Node *get_advise_node_ptr, std::vector< Node * > &result_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) const;
	virtual bool adviseRunNode( const Node *const node ) const;
	virtual Node * getBeforeNode( ) const;
	virtual Node * getCurrentNode( ) const;
	virtual const std::vector< Node * > & getAdviseNodeVector( ) const;
	virtual const std::vector< Node * > & getLinkNodeVector( ) const;
	virtual const std::vector< Node * > & getOverRunNodeVector( ) const;
	virtual const std::vector< Node * > & getStartNodeVector( ) const;
	virtual bool linkHasStartNode( const Node *const check_start_node_ptr ) const;
	virtual bool isOver( ) const;
	virtual bool isReady( ) const;
	virtual bool linkHasNode( const Node *const check_node_ptr ) const;
	virtual bool linkHasEndNode( const Node *const check_node_ptr ) const;
	virtual bool sortBilderList( const std::vector< Node * > &reference_sort_vector );
};

#endif // NODERUNLINK_H_H_HEAD__FILE__
