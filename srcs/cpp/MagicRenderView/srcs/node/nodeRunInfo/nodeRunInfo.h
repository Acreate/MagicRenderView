#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__

#include <QObject>

class PrinterDirector;
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
	/// @brief 输出对象
	PrinterDirector *printerDirector;
	/// @brief 当前帧
	size_t currentFrame;
	/// @brief 最大帧
	size_t maxFrame;
	/// @brief 是否停止
	bool runStop;
	/// @brief 是否准备完成
	bool ready;
	/// @brief 下一个节点事件
	qint64 nextRunNodeTime;
	/// @brief 编译时间
	QDateTime *builderDataTime;
	/// @brief 上一个节点运行时间
	QDateTime *brforeRunDataTime;
	/// @brief 当前节点运行时间
	QDateTime *currentRunDataTime;
	/// @brief 当前执行节点
	Node *currentNode;
	/// @brief 以前的节点
	Node *oldNode;
	/// @brief 编译列表
	std::vector< Node * > builderNodeVector;
	/// @brief 编译链接当中的创建节点序列
	std::vector< NodeRunLink * > createVector;
	/// @brief 编译链接当中的点节点序列
	std::vector< NodeRunLink * > pointVector;
	/// @brief 编译链接当中的函数节点序列
	std::vector< NodeRunLink * > functionVector;
	/// @brief 链接列表
	std::vector< NodeRunLink * > nodeRunLinkVector;
	/// @brief 调用栈
	std::vector< NodeRunLink * > functionStack;
	/// @brief 进程栈
	std::vector< NodeRunLink * > createStack;
	/// @brief 定点栈
	std::vector< NodeRunLink * > pointStack;
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
	/// @brief 重置数据
	virtual void resetData( );
	/// @brief 获取下一个节点对象指针
	/// @param result_next_node_ptr 返回的下一个节点
	/// @return 失败返回 null
	virtual bool getNextNodeRunLinkPtr( NodeRunLink * &result_next_node_ptr );
	/// @brief 更新下一个节点堆栈信息
	/// @param update_next_node_ptr 更新的节点链接信息
	/// @return 失败返回 false
	virtual bool updateNextNodeRunLinkPtr( NodeRunLink *update_next_node_ptr );
	/// @brief 检查序列是否存在匹配的起始节点
	/// @param check_vector 检查的序列
	/// @param check_node 起始节点
	/// @return 不存在返回 false
	virtual bool stackHasStartNode( const std::vector< NodeRunLink * > &check_vector, Node *check_node ) const;
public:
	NodeRunInfo( );
	~NodeRunInfo( ) override;
	virtual bool isReady( ) const { return ready; }
	virtual bool hasBuilderNode( const Node *check_node_ptr );
	virtual int getMsleepTime( ) const { return nextRunNodeTime; }
	virtual void setMsleepTime( int msleep_time ) { nextRunNodeTime = msleep_time; }
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
	/// @brief 开始编译
	/// @param change_obj 编译对象
	void start_builder_signal( NodeRunInfo *change_obj );
	/// @brief 编译结束
	/// @param change_obj 编译对象
	void end_builder_signal( NodeRunInfo *change_obj );
	/// @brief 编译完成信号
	/// @param builder_link 完成对象
	void builder_finish_signal( NodeRunLink *builder_link );
	/// @brief 编译警告信号
	/// @param builder_link 警告对象
	void builder_warning_signal( NodeRunLink *builder_link );
	/// @brief 编译错误信号
	/// @param builder_link 错误对象
	void builder_error_signal( NodeRunLink *builder_link );
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
