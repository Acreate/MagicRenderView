#ifndef NODEBUILDERTOOLS_H_H_HEAD__FILE__
#define NODEBUILDERTOOLS_H_H_HEAD__FILE__
#pragma once
#include <QString>

class NodeRefLinkInfo;
class NodeBuilderTools {
protected:
	/// @brief 填充依赖到指定序列当中
	/// @param analysis_node_ref_link_info 依据的依赖对象
	/// @param result_node_ref_link_vector 填充依赖返回(输入/输出)
	static void analysisSubNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< NodeRefLinkInfo * > &result_node_ref_link_vector );
public:
	/// @brief 填充依赖到指定序列当中
	/// @param analysis_node_ref_link_info 依据的依赖对象
	/// @param result_node_ref_link_vector 填充依赖返回(输入/输出)
	static bool analysisNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< NodeRefLinkInfo * > &result_node_ref_link_vector );
	/// @brief 去除重复，会使用数组进行重新排序，但不会影响长度
	/// @param check_array_ptr 检测的数组
	/// @param check_array_count 检测长度
	/// @return 非重复数量
	static size_t filterRepetition( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count );
	/// @brief 节点数组转换到字符串
	/// @param check_array_ptr 数组起始地址
	/// @param check_array_count 数组长度
	/// @return 字符串
	static QString toQString( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count );
};

#endif // NODEBUILDERTOOLS_H_H_HEAD__FILE__
