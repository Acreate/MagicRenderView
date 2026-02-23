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
}

#endif // NODETOOLS_H_H_HEAD__FILE__
