#ifndef NODETOOLS_H_H_HEAD__FILE__
#define NODETOOLS_H_H_HEAD__FILE__
#pragma once
#include <vector>

class Node;
class NodeTools {
public:
	/// @brief 获取节点列表依赖，依赖包含输出依赖（被依赖）与输入依赖（自身依赖）
	/// @param check_node_vector 检查的依赖列表
	/// @param result_ref_node_vector 返回的依赖列表
	/// @return 失败返回 false
	static bool getNodeVectorRefNodeVector( const std::vector< Node * > &check_node_vector, std::vector< Node * > &result_ref_node_vector );
	/// @brief 根据依赖进行排序
	/// @param check_node_vector 排序节点列表
	/// @param result_ref_node_vector 返回的排序
	/// @return 失败返回 false
	static bool sortNodeVectorRefNodeVector( const std::vector< Node * > &check_node_vector, std::vector< Node * > &result_ref_node_vector );
};

#endif // NODETOOLS_H_H_HEAD__FILE__
