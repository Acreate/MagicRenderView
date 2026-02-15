#ifndef NODERUNLINK_H_H_HEAD__FILE__
#define NODERUNLINK_H_H_HEAD__FILE__
#include <QObject>

class NodeRunLinkData;
class NodeRunInfo;
class Node;
class NodeRunLink : public QObject {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	NodeRunLinkData *nodeRunLinkDataPtr;
public:
	~NodeRunLink( ) override;
	virtual NodeRunLinkData * getNodeRunLinkDataPtr( ) const;
protected:
	NodeRunLink( Node *const init_node_ptr );
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
	/// @brief 节点是否建议运行
	/// @param node 检测的节点
	/// @return true 表示建议运行
	virtual bool adviseRunNode( const Node *const node ) const;
	/// @brief 链接节点
	/// @return 失败返回 false
	virtual bool builder( ) = 0;
	/// @brief 链接当中是否存在节点
	/// @param check_node_ptr 检查节点
	/// @return 不存在返回 false
	virtual bool linkHasNode( const Node *const check_node_ptr ) const;
	/// @brief 获取下一个运行节点
	/// @param result_next_node_ptr 下一个运行节点
	/// @return 失败返回 false
	virtual bool getNextRunNode( Node *&result_next_node_ptr ) = 0;
};

#endif // NODERUNLINK_H_H_HEAD__FILE__
