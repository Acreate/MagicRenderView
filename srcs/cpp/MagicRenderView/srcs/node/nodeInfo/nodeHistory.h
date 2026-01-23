#ifndef NODEHISTORY_H_H_HEAD__FILE__
#define NODEHISTORY_H_H_HEAD__FILE__

#include <QObject>
#include <functional>
// todo : 改进该类，实现节点更多操作
class NodeHistory : public QObject {
	Q_OBJECT;
protected:
	/// @brief 当前操作函数
	std::function< NodeHistory*( ) > currentOperate;
	/// @brief 取消操作函数
	std::function< NodeHistory*( ) > cancelOperate;
public:
	~NodeHistory( ) override { }
	NodeHistory( const std::function< NodeHistory*( ) > &current_operate, const std::function< NodeHistory*( ) > &cancel_operate );
	/// @brief 调用当前操作（重复）
	/// @return 失败返回 nullptr
	virtual NodeHistory * callCurrentOperate( );
	/// @brief 调用取消当前操作
	/// @return 失败返回 nullptr
	virtual NodeHistory * callCancelOperate( );
};

#endif // NODEHISTORY_H_H_HEAD__FILE__
