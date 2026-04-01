#ifndef NODERUNINFOSTACK_H_H_HEAD__FILE__
#define NODERUNINFOSTACK_H_H_HEAD__FILE__
#include <QObject>

class NodeRunInfoData;
class NodeRunInfoStack : public QObject {
	Q_OBJECT;
private:
	/// @brief 创建节点队列
	std::list< NodeRunInfoData * > create;
	/// @brief 跳转节点队列
	std::list< NodeRunInfoData * > point;
	/// @brief 函数节点队列
	std::list< NodeRunInfoData * > function;
public:
	virtual bool popCreateStackLast( NodeRunInfoData &result_info );
	virtual bool pushCreateStackLast( const NodeRunInfoData &push_create_node );
	virtual bool popPointStackLast( NodeRunInfoData &result_info );
	virtual bool pushPointStackLast( const NodeRunInfoData &push_point_node );
	virtual bool popFcuntionStackLast( NodeRunInfoData &result_info );
	virtual bool pushFcuntionStackLast( const NodeRunInfoData &push_function_node );
	~NodeRunInfoStack( ) override;
};

#endif // NODERUNINFOSTACK_H_H_HEAD__FILE__
