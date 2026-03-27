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
	Node *currentOver;
	bool empty;
protected:
	NodeRunLink( Node *const init_node_ptr );
	/// @brief 是否为空
	/// @return true 表示为空
	virtual bool isEmpty( ) const {
		return empty;
	}
	/// @brief 链接节点
	/// @return 失败返回 false
	virtual bool builder( ) = 0;
	/// @brief 获取下一个运行节点
	/// @param over_run_node_vector 运行完毕列表
	/// @param result_next_node_ptr 下一个运行节点
	/// @return 失败返回 false
	virtual bool getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr );
	/// @brief 运行节点
	/// @param run_time 运行时间
	/// @param run_frame 运行帧
	/// @return 成功返回 true
	virtual bool runRunNode( const QDateTime &run_time, size_t run_frame );
	virtual bool adviseRunNode( const Node *const node ) const;
	/// @brief 过滤弃用节点
	/// @param filter_target_ref_src_vector 过滤引用序列
	/// @return 失败返回 false
	virtual bool filterDeprecatedNode( std::vector< Node * > &filter_target_ref_src_vector );
	virtual Node * getBeforeNode( ) const;
	virtual Node * getCurrentNode( ) const;
	virtual const std::list< Node * > & getAdviseNodeVector( ) const;
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
