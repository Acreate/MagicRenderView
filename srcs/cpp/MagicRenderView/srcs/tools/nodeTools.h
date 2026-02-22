#ifndef NODETOOLS_H_H_HEAD__FILE__
#define NODETOOLS_H_H_HEAD__FILE__
#include <vector>

class Node;
namespace NodeTools {
	/// @brief 递归获取节点的所有依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
	/// @brief 递归获取节点的所有输入依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeInputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
	/// @brief 递归获取节点的所有输出依赖
	/// @param get_node_target 获取节点
	/// @param result_ref_node_vector 依赖列表
	/// @return 失败返回 false
	bool getNodeOutputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector );
	/// @brief 从原生列表当中删除过滤节点列表
	/// @param src_vector 原生列表
	/// @param target_vector 过滤列表
	/// @return 返回过滤个数
	std::vector< Node * > filterNodeVector( const std::vector< Node * > &src_vector, const std::vector< Node * > &target_vector );
}

#endif // NODETOOLS_H_H_HEAD__FILE__
