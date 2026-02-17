#ifndef NODERUNLINKDATA_H_H_HEAD__FILE__
#define NODERUNLINKDATA_H_H_HEAD__FILE__
#include <QObject>
#include <vector>
class NodeRunLink;
class Node;
class NodeRunLinkData : public QObject {
protected:
	/// @brief 保存已经运行的节点
	std::vector< Node * > overRunNodeVector;
	/// @brief 节点链表
	std::vector< Node * > linkNodeVector;
	/// @brief 建议列表
	std::vector< Node * > adviseNodeVector;
	/// @brief 开始节点
	std::vector< Node * > startNodeVector;
	/// @brief 当前的节点
	Node *currentNode;
	/// @brief 之前的节点
	Node *beforeNode;
	/// @brief 是否运行完毕
	bool over;
	/// @brief 是否准备完毕
	bool ready;
protected:
	/// @brief 创建链接对象
	/// @brief 使用功能之前，需要调用 builder()。
	/// @brief 可以使用 isReady( ) 验证是否可用
	NodeRunLinkData( Node *init_node_ptr );
	/// @brief 获取运行完毕的节点列表
	/// @return 完成序列
	virtual const std::vector< Node * > & getOverRunNodeVector( ) const;
	/// @brief 获取链表内节点序列
	/// @return 链表内节点序列
	virtual const std::vector< Node * > & getLinkNodeVector( ) const;
	/// @brief 获取建议节点序列
	/// @return 建议节点序列
	virtual const std::vector< Node * > & getAdviseNodeVector( ) const;
	/// @brief 获取起始节点列表
	/// @return 起始节点列表
	virtual const std::vector< Node * > & getStartNodeVector( ) const;
	/// @brief 获取节点的依赖列表
	/// @param get_ref_node_ptr 获取的节点
	/// @param result_ref_node_vector 依赖运行列表
	/// @param ndoe_run_start_data_time 当前运行时间
	/// @param current_frame 当前帧
	/// @return 失败返回 false
	virtual bool getNodeRunRefNodeVector( Node *get_ref_node_ptr, std::vector< Node * > &result_ref_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) const;
	/// @brief 获取节点的建议列表
	/// @param get_advise_node_ptr 获取的节点
	/// @param result_advise_node_vector 建议运行列表
	/// @param ndoe_run_start_data_time 当前运行时间
	/// @param current_frame 当前帧
	/// @return 失败返回 false
	virtual bool getNodeRunAdviseNodeVector( Node *get_advise_node_ptr, std::vector< Node * > &result_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) const;
	/// @brief 是否可用对象
	/// @return 不可用返回 false
	virtual bool isReady( ) const;
	/// @brief 是否运行完毕
	/// @return true 表示运行完毕
	virtual bool isOver( ) const;
	/// @brief 获取当前运行节点
	/// @return 当前运行节点对象指针
	virtual Node * getCurrentNode( ) const;
	/// @brief 获取上一次运行的节点
	/// @return 当一次运行的节点指针
	virtual Node * getBeforeNode( ) const;
	/// @brief 节点是否建议运行
	/// @param node 检测的节点
	/// @return true 表示建议运行
	virtual bool adviseRunNode( const Node *const node ) const;
	/// @brief 链接当中是否存在节点
	/// @param check_node_ptr 检查节点
	/// @return 不存在返回 false
	virtual bool linkHasNode( const Node *const check_node_ptr ) const;
	/// @brief 链接当中是否存在起始节点
	/// @param check_start_node_ptr 检查的起始节点
	/// @return 不存在返回 false
	virtual bool linkHasStartNode( const Node *const check_start_node_ptr ) const;
};

#endif // NODERUNLINKDATA_H_H_HEAD__FILE__
