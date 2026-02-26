#ifndef NODERUNLINKTOOLS_H_H_HEAD__FILE__
#define NODERUNLINKTOOLS_H_H_HEAD__FILE__
#include <vector>

class NodeRunLinkData;
class Node;
namespace NodeRunLinkTools {
	class Get {
		friend class NodeRunLink;
	public:
		virtual ~Get( ) = default;

		virtual std::vector< Node * > & getAdviseNodeVector( ) const;
		virtual std::vector< Node * > & getLinkNodeVector( ) const;
		virtual std::vector< Node * > & getOverRunNodeVector( ) const;
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
