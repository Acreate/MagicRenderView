#ifndef NODERUNLINKTOOLS_H_H_HEAD__FILE__
#define NODERUNLINKTOOLS_H_H_HEAD__FILE__
#include <list>
#include <vector>

class Node;
namespace NodeRunLinkTools {
	
	/// @brief 递归获取节点的所有依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
	/// @brief 排序列表
	/// @param ref_sort_node_vector 参考排序
	/// @param result_ref_node_vector 返回排序完毕的序列
	/// @return 失败返回 false
	bool sortNodeRef( const std::vector< Node * > &ref_sort_node_vector, std::vector< Node * > &result_ref_node_vector );

	/// @brief 排序列表
	/// @param ref_begin_sort_node_vector 参考开始排序
	/// @param ref_sort_node_vector 参考排序，该序列必须包含 ref_begin_sort_node_vector
	/// @param result_ref_node_vector 返回排序完毕的序列
	/// @return 失败返回 false
	bool sortNodeRef( const std::vector< Node * > &ref_begin_sort_node_vector, const std::vector< Node * > &ref_sort_node_vector, std::vector< Node * > &result_ref_node_vector );

	/// @brief 递归获取节点的所有输入依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeInputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
	/// @brief 递归获取节点的所有输出依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeOutputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
}

#endif // NODERUNLINKTOOLS_H_H_HEAD__FILE__
