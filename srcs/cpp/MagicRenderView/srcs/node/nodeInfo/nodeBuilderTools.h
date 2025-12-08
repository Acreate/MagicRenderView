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

	/// @brief 查找第一个匹配的开始节点
	/// @param analysis_node_ref_link_info 查找对象指针
	/// @param result_begin_node_ref_link 返回第一个匹配的开始对象指针
	/// @return 不存在返回 false
	static bool findRefBeginNode( NodeRefLinkInfo *analysis_node_ref_link_info, NodeRefLinkInfo * &result_begin_node_ref_link );
	/// @brief 去除重复，会使用数组进行重新排序，但不会影响长度
	/// @param check_array_ptr 检测的数组
	/// @param check_array_count 检测长度
	/// @return 非重复数量
	static size_t filterRepetition( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count );
	/// @brief 排序进程节点，会忽略引用的输入开始节点
	/// @param sort_array_ptr 排序的数组起始地址
	/// @param sort_array_count 排序的数组数量
	static bool sortProcessNodeRefArray( NodeRefLinkInfo **sort_array_ptr, const size_t &sort_array_count );
	/// @brief 节点数组转换到字符串
	/// @param check_array_ptr 数组起始地址
	/// @param check_array_count 数组长度
	/// @return 字符串
	static QString toQString( const NodeRefLinkInfo *const*check_array_ptr, const size_t &check_array_count );
	/// @brief 节点数组转换到字符串
	/// @param conver_std_vector_node_ref_link_infosodeRefLinkInfo 转换序列
	/// @return 字符串
	static QString toQString( const std::vector< NodeRefLinkInfo * > &conver_std_vector_node_ref_link_infosodeRefLinkInfo ) {
		NodeRefLinkInfo *const *converStdVectorNodeRefLinkInfosodeRefLinkInfo = conver_std_vector_node_ref_link_infosodeRefLinkInfo.data( );
		return toQString( converStdVectorNodeRefLinkInfosodeRefLinkInfo, conver_std_vector_node_ref_link_infosodeRefLinkInfo.size( ) );
	}
	class JumpNodeBuilderTools {
	protected:
		/// @brief 匹配输入的节点路径
		/// @param analysis_node_ref_link_info 查找的路径
		/// @param result_input_node_ref_map 输入依赖列表
		/// @param result_node_ref_link_vector 返回路径列表
		/// @return 失败返回 false
		static bool findPoint( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector<std::pair<NodeRefLinkInfo *, NodeRefLinkInfo *>> &result_input_node_ref_map, std::vector<NodeRefLinkInfo *> &result_node_ref_link_vector );
	public:
		/// @brief 填充依赖到指定序列当中，
		/// @param analysis_node_ref_link_info 依据的依赖对象
		/// @param result_node_ref_link_vector 填充依赖返回(输入/输出)
		static bool analysisJumpNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< std::vector< NodeRefLinkInfo * > > &result_node_ref_link_vector );
	};
};

#endif // NODEBUILDERTOOLS_H_H_HEAD__FILE__
