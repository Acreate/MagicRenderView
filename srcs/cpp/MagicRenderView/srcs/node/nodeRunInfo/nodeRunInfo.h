#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__

#include <QObject>

class NodeRunLink;
class QDateTime;
class Application;
namespace NodeEnum {
	enum class ErrorType;
	enum class AdviseType;
}
class Node;
class NodeDirector;
class SrackInfo;
class NodeRunInfo : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
protected:
	/// @brief 应用实例
	Application *appinstancePtr;
	/// @brief 当前帧
	size_t currentFrame;
	/// @brief 最大帧
	size_t maxFrame;
	/// @brief 是否停止
	bool isRunStop;
	/// @brief 休眠时间
	int msleepTime;
	/// @brief 编译时间
	QDateTime *builderDataTime;
	/// @brief 上一个节点运行时间
	QDateTime *brforeRunDataTime;
	/// @brief 当前节点运行时间
	QDateTime *currentRunDataTime;
	/// @brief 等待下一面
	long long waiteNextNodeTime;

	/// @brief 编译列表
	std::vector< Node * > builderNodeVector;
	/// @brief 链接列表
	std::vector< NodeRunLink * > nodeRunLinkVector;
	/// @brief 调用栈
	std::list< NodeRunLink * > callStack;
	/// @brief 进程栈
	std::list< NodeRunLink * > processStack;
	/// @brief 定点栈
	std::list< NodeRunLink * > pointStack;
protected:
	virtual void appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count );
	virtual void appendBuilderNode( std::vector< Node * > &append_node_vector ) {
		appendBuilderNode( append_node_vector.data( ), append_node_vector.size( ) );
	}
	virtual void appendBuilderNode( Node *append_node_unity );
	virtual void removeBuilderNode( Node *append_node_unity );
	/// @brief 编译实例
	/// @return 失败返回 false
	virtual bool builderRunInstance( );
public:
	NodeRunInfo( );
	~NodeRunInfo( ) override;
	virtual bool hasBuilderNode( const Node *check_node_ptr );
	virtual int getMsleepTime( ) const { return msleepTime; }
	virtual void setMsleepTime( int msleep_time ) { msleepTime = msleep_time; }
	virtual long long getWaiteNextNodeTime( ) const { return waiteNextNodeTime; }
	virtual void setWaiteNextNodeTime( long long waite_next_node_time ) { waiteNextNodeTime = waite_next_node_time; }
	/// @brief 运行下一个
	/// @return 成功返回 true
	virtual bool runNextNode( );
	/// @brief 运行剩余
	/// @return 成功返回 true
	virtual bool runResidueNode( );
	/// @brief 运行到下一帧
	/// @return 成功返回 true
	virtual bool runToNextFrame( );
	/// @brief 运行到指定节点
	/// @param target 指定的节点
	/// @return 失败返回 false
	virtual bool runToNode( const Node *target );
	/// @brief 重置开始
	/// @return 成功返回 true
	virtual bool resetRunStartNode( );
	/// @brief 停止运行
	/// @return 成功返回 true
	virtual bool runStopNode( );
	/// @brief 清理所有
	virtual void clear( );
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_obj_ptr 释放对象指针
	/// @param srack_info 信号行
	void release_signal( NodeRunInfo *release_obj_ptr, const SrackInfo &srack_info );
	/// @brief 清理对象产生信号
	/// @param clear_obj 清理对象
	/// @param srack_info 信号堆栈
	void clear_signal( NodeRunInfo *clear_obj, const SrackInfo &srack_info );
	/// @brief 当自动运行状态被改变时，发出该信号
	/// @param change_obj 信号对象 
	/// @param new_status 新的状态
	void auto_run_status_change_signal( NodeRunInfo *change_obj, bool new_status );
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
