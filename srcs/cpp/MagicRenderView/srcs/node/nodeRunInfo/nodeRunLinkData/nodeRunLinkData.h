#ifndef NODERUNLINKDATA_H_H_HEAD__FILE__
#define NODERUNLINKDATA_H_H_HEAD__FILE__
#include <vector>
class NodeRunLink;
class Node;
class NodeRunLinkData {
	friend class NodeRunLink;
protected:
	/// @brief 保存已经运行的节点
	std::vector< Node * > overRunNodeVector;
	/// @brief 节点链表
	std::vector< Node * > linkNodeVector;
	/// @brief 建议列表
	std::vector< Node * > adviseNodeVector;
	/// @brief 开始节点
	Node *startNode;
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
public:
	virtual ~NodeRunLinkData( ) = default;
	/// @brief 是否可用对象
	/// @return 不可用返回 false
	virtual bool isReady( ) const;
	/// @brief 是否运行完毕
	/// @return true 表示运行完毕
	virtual bool isOver( ) const;
	/// @brief 获取开始节点
	/// @return 开始节点对象指针
	virtual Node * getStartNode( ) const;
	/// @brief 获取当前运行节点
	/// @return 当前运行节点对象指针
	virtual Node * getCurrentNode( ) const;
	/// @brief 获取上一次运行的节点
	/// @return 当一次运行的节点指针
	virtual Node * getBeforeNode( ) const;
};


#endif // NODERUNLINKDATA_H_H_HEAD__FILE__
