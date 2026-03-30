#ifndef NODERUNINFODATA_H_H_HEAD__FILE__
#define NODERUNINFODATA_H_H_HEAD__FILE__
#include <QObject>
class NodeRunInfo;
class Node;
class NodeRunInfoData : public QObject {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
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
	/// @brief 临时使用节点指针
	Node *buffNode;
	/// @brief 当前执行节点
	Node *currentNode;
	/// @brief 以前的节点
	Node *oldNode;
	/// @brief 编译列表
	std::vector< Node * > builderNodeVector;
	/// @brief 编译时的起始节点列表
	std::vector< Node * > builderBeginList;
	/// @brief 编译节点的排序参考列表
	std::vector< Node * > builderReferenceSortVector;
	/// @brief 已经调用完毕的列表
	std::vector< Node * > runOverNodeVector;
public:
	NodeRunInfoData( );
protected:
	/// @brief 拷贝数据到该对象
	/// @param copy_target_ptr 拷贝目标
	/// @return 失败返回 false
	virtual bool copyNodeRunInfoDataToThis( const NodeRunInfoData * const copy_target_ptr );
	/// @brief 获取当前帧
	/// @return 帧
	virtual size_t getCurrentFrame( ) const { return currentFrame; }
	virtual void setCurrentFrame( size_t current_frame ) { currentFrame = current_frame; }
	virtual size_t getMaxFrame( ) const { return maxFrame; }
	virtual void setMaxFrame( size_t max_frame ) { maxFrame = max_frame; }
	virtual bool isRunStop( ) const { return runStop; }
	virtual void setRunStop( bool run_stop ) { runStop = run_stop; }
	virtual bool isReady( ) const { return ready; }
	virtual void setReady( bool ready ) { this->ready = ready; }
	virtual qint64 getNextRunNodeTime( ) const { return nextRunNodeTime; }
	virtual void setNextRunNodeTime( qint64 next_run_node_time ) { nextRunNodeTime = next_run_node_time; }
	virtual QDateTime * getBuilderDataTime( ) const { return builderDataTime; }
	virtual void setBuilderDataTime( QDateTime *builder_data_time ) { builderDataTime = builder_data_time; }
	virtual QDateTime * getBrforeRunDataTime( ) const { return brforeRunDataTime; }
	virtual void setBrforeRunDataTime( QDateTime *brfore_run_data_time ) { brforeRunDataTime = brfore_run_data_time; }
	virtual QDateTime * getCurrentRunDataTime( ) const { return currentRunDataTime; }
	virtual void setCurrentRunDataTime( QDateTime *current_run_data_time ) { currentRunDataTime = current_run_data_time; }
	virtual Node * getBuffNode( ) const { return buffNode; }
	virtual void setBuffNode( Node *buff_node ) { buffNode = buff_node; }
	virtual Node * getCurrentNode( ) const { return currentNode; }
	virtual void setCurrentNode( Node *current_node ) { currentNode = current_node; }
	virtual Node * getOldNode( ) const { return oldNode; }
	virtual void setOldNode( Node *old_node ) { oldNode = old_node; }
	virtual const std::vector< Node * > & getBuilderNodeVector( ) const { return builderNodeVector; }
	virtual void setBuilderNodeVector( const std::vector< Node * > &builder_node_vector ) { builderNodeVector = builder_node_vector; }
	virtual const std::vector< Node * > & getBuilderBeginList( ) const { return builderBeginList; }
	virtual void setBuilderBeginList( const std::vector< Node * > &builder_begin_list ) { builderBeginList = builder_begin_list; }
	virtual const std::vector< Node * > & getBuilderReferenceSortVector( ) const { return builderReferenceSortVector; }
	virtual void setBuilderReferenceSortVector( const std::vector< Node * > &builder_reference_sort_vector ) { builderReferenceSortVector = builder_reference_sort_vector; }
	virtual const std::vector< Node * > & getRunOverNodeVector( ) const { return runOverNodeVector; }
	virtual void setRunOverNodeVector( const std::vector< Node * > &run_over_node_vector ) { runOverNodeVector = run_over_node_vector; }
};

#endif // NODERUNINFODATA_H_H_HEAD__FILE__
