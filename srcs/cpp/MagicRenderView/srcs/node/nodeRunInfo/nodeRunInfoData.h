#ifndef NODERUNINFODATA_H_H_HEAD__FILE__
#define NODERUNINFODATA_H_H_HEAD__FILE__
#include <QObject>

class Node;
class NodeRunLink;
class NodeRunInfoData : public QObject {
	Q_OBJECT;
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
	/// @brief 编译链接当中的创建节点序列
	std::vector< NodeRunLink * > createVector;
	/// @brief 编译链接当中的点节点序列
	std::vector< NodeRunLink * > pointVector;
	/// @brief 编译链接当中的函数节点序列
	std::vector< NodeRunLink * > functionVector;
	/// @brief 链接列表
	std::vector< NodeRunLink * > nodeRunLinkVector;
	/// @brief 调用栈
	std::list< NodeRunLink * > functionStack;
	/// @brief 进程栈
	std::list< NodeRunLink * > createStack;
	/// @brief 定点栈
	std::list< NodeRunLink * > pointStack;
public:
	NodeRunInfoData( );
	virtual bool copyTargetToThis( const NodeRunInfoData *const other );
	virtual size_t getCurrentFrame( ) const { return currentFrame; }
	virtual size_t getMaxFrame( ) const { return maxFrame; }
	virtual bool isRunStop( ) const { return runStop; }
	virtual bool isReady( ) const { return ready; }
	virtual qint64 getNextRunNodeTime( ) const { return nextRunNodeTime; }
	virtual QDateTime * getBuilderDataTime( ) const { return builderDataTime; }
	virtual QDateTime * getBrforeRunDataTime( ) const { return brforeRunDataTime; }
	virtual QDateTime * getCurrentRunDataTime( ) const { return currentRunDataTime; }
	virtual Node * getBuffNode( ) const { return buffNode; }
	virtual Node * getCurrentNode( ) const { return currentNode; }
	virtual Node * getOldNode( ) const { return oldNode; }
	virtual const std::vector< Node * > & getBuilderNodeVector( ) const { return builderNodeVector; }
	virtual const std::vector< Node * > & getBuilderBeginList( ) const { return builderBeginList; }
	virtual const std::vector< Node * > & getBuilderReferenceSortVector( ) const { return builderReferenceSortVector; }
	virtual const std::vector< Node * > & getRunOverNodeVector( ) const { return runOverNodeVector; }
	virtual const std::vector< NodeRunLink * > & getCreateVector( ) const { return createVector; }
	virtual const std::vector< NodeRunLink * > & getPointVector( ) const { return pointVector; }
	virtual const std::vector< NodeRunLink * > & getFunctionVector( ) const { return functionVector; }
	virtual const std::vector< NodeRunLink * > & getNodeRunLinkVector( ) const { return nodeRunLinkVector; }
	virtual const std::list< NodeRunLink * > & getFunctionStack( ) const { return functionStack; }
	virtual const std::list< NodeRunLink * > & getCreateStack( ) const { return createStack; }
	virtual const std::list< NodeRunLink * > & getPointStack( ) const { return pointStack; }
};

#endif // NODERUNINFODATA_H_H_HEAD__FILE__
