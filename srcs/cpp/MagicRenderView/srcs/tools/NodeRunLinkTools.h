#ifndef NODERUNLINKTOOLS_H_H_HEAD__FILE__
#define NODERUNLINKTOOLS_H_H_HEAD__FILE__
#include <list>
#include <vector>

class NodeRunLinkData;
class Node;
namespace NodeRunLinkTools {
	class Get {
		friend class NodeRunLink;
	public:
		virtual ~Get( ) = default;
		/// @brief 获取建议列表引用
		/// @return 建议列表引用
		virtual std::list<Node *> & getAdviseNodeVector( ) const;
		/// @brief 获取关联列表引用
		/// @return 关联列表引用
		virtual std::vector< Node * > & getLinkNodeVector( ) const;
		/// @brief 获取运行完成列表引用
		/// @return 运行完成引用
		virtual std::vector< Node * > & getOverRunNodeVector( ) const;
		/// @brief 获取起始节点列表引用
		/// @return 起始列表引用
		virtual std::vector< Node * > & getStartNodeVector( ) const;

		/// @brief 递归获取节点的所有依赖
		/// @param result_ref_node_vector 依赖列表
		/// @return 失败返回 false
		virtual bool getNodeRef( std::vector< Node * > &result_ref_node_vector );

		/// @brief 递归获取节点的所有输入依赖
		/// @param result_ref_node_vector 依赖列表
		/// @return 失败返回 false
		virtual bool getNodeInputInForRef( std::vector< Node * > &result_ref_node_vector );
		/// @brief 递归获取节点的所有输出依赖
		/// @param result_ref_node_vector 依赖列表
		/// @return 失败返回 false
		virtual bool getNodeOutputInForRef( std::vector< Node * > &result_ref_node_vector );
	private:
		NodeRunLinkData *nodeRunLinkData;
		Get( NodeRunLinkData *const node_run_link_data )
			: nodeRunLinkData( node_run_link_data ) { }
	};

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
