#ifndef NODERUNLINK_H_H_HEAD__FILE__
#define NODERUNLINK_H_H_HEAD__FILE__
#include <QObject>

class NodeRunInfo;
class Node;

class NodeRunLink : public QObject {
	Q_OBJECT;
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
	NodeRunLink( Node *init_node_ptr );
	/// @brief 是否可用对象
	/// @return 不可用返回 false
	virtual bool isReady( ) const {
		return ready;
	}
	/// @brief 是否运行完毕
	/// @return true 表示运行完毕
	virtual bool isOver( ) const {
		return over;
	}
	/// @brief 节点是否建议运行
	/// @param node 检测的节点
	/// @return true 表示建议运行
	virtual bool adviseRunNode( const Node *const node ) const;
	/// @brief 运行节点
	/// @param date_time 运行时间
	/// @param frame 当前帧
	/// @return 失败返回 false
	virtual bool runNode( const QDateTime &date_time, size_t frame );
	/// @brief 获取开始节点
	/// @return 开始节点对象指针
	virtual Node * getStartNode( ) const { return startNode; }
	/// @brief 获取当前运行节点
	/// @return 当前运行节点对象指针
	virtual Node * getCurrentNode( ) const { return currentNode; }
	/// @brief 获取上一次运行的节点
	/// @return 当一次运行的节点指针
	virtual Node * getBeforeNode( ) const { return beforeNode; }
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
	/// @brief 返回当前运行节点
	/// @param result_current_node_ptr 当前运行节点
	/// @return 失败返回 false
	virtual bool getCurrentRunNode( Node * &result_current_node_ptr ) = 0;
};

#endif // NODERUNLINK_H_H_HEAD__FILE__
