#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__

#include <QObject>

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
	using TRunBodyObj = Node;
	using TRunBodyObjPtr = TRunBodyObj *;
protected:
	/// @brief 应用实例
	Application *appinstancePtr;
	/// @brief 当前帧
	size_t currentFrame;
	/// @brief 最大帧
	size_t maxFrame;
	/// @brief 是否停止
	bool isRunStop;
	/// @brief 编译时间
	QDateTime *builderDataTime;
	/// @brief 上一个节点运行时间
	QDateTime *brforeRunDataTime;
	/// @brief 当前节点运行时间
	QDateTime *currentRunDataTime;
	/// @brief 等待下一面
	long long waiteNextTime;
	/// @brief 当前对象指针
	TRunBodyObjPtr currentRunPtr;
	/// @brief 编译列表
	std::vector< TRunBodyObjPtr > builderNodeVector;
	/// @brief 编译列表指针
	TRunBodyObjPtr *builderNodeArrayPtr;
	/// @brief 编译列表个数
	size_t builderNodeArrayCount;
	/// @brief 完成列表
	std::vector< TRunBodyObjPtr > overRunNodeVector;
	/// @brief 完成列表指针
	TRunBodyObjPtr *overRunNodeArrayPtr;
	/// @brief 完成列表个数
	size_t overRunNodeArrayCount;
	/// @brief 等待列表
	std::vector< TRunBodyObjPtr > waiteRunNodeVector;
	/// @brief 建议列表
	std::vector< TRunBodyObjPtr > adviseNodeVector;
	/// @brief 开始列表
	std::vector< TRunBodyObjPtr > beginNodeVector;
	/// @brief 起始列表指针
	TRunBodyObjPtr *beginNodeArrayPtr;
	/// @brief 起始列表个数
	size_t beginNodeArrayCount;
protected:
	virtual void appendBuilderNode( TRunBodyObj **append_node_array_ptr, const size_t &append_node_array_count );
	virtual void appendBuilderNode( std::vector< TRunBodyObj * > &append_node_vector ) {
		appendBuilderNode( append_node_vector.data( ), append_node_vector.size( ) );
	}
	virtual void appendBuilderNode( TRunBodyObj *append_node_unity );
	virtual void removeBuilderNode( TRunBodyObj *append_node_unity );
	/// @brief 节点是否已经运行完毕
	/// @param check_next_node 检查节点
	/// @return 已经实现运行，返回 true
	virtual bool isOverRunNode( Node *check_next_node );
	/// @brief 判定是否可以运行（根据输入端依赖是否实现运行判定）
	/// @param check_next_node 判定节点
	/// @return 返回 true 表示支持运行
	virtual bool isRunNode( Node *check_next_node );
	/// @brief 编译实例
	/// @return 失败返回 false
	virtual bool builderRunInstance( );
	/// @brief 编译实例引用
	/// @return 失败返回 false
	virtual bool builderRunInstanceRef( );
	/// @brief 查找运行节点
	/// @param result_run_node 返回的运行节点
	/// @return 失败返回 false
	virtual bool findNextRunNode( Node * &result_run_node );
	/// @brief 运行指定节点
	/// @param run_node 运行的节点
	/// @return 成功返回 true
	virtual bool runCurrentNode( Node *run_node );
	/// @brief 运行完成节点
	/// @return 成功返回 true
	virtual bool overRunNode( );
	/// @brief 过滤存储列表，筛选建议列表列表存储到匹配列表
	/// @return 成功返回 true
	virtual bool filterToAdviseVector( );
public:
	NodeRunInfo( );
	~NodeRunInfo( ) override;
	/// @brief 检查是否存在指定节点
	/// @param check_node_ref 检查节点
	/// @return 不存在返回 false
	virtual bool hasNodeRefInRunVector( TRunBodyObj *check_node_ref );
	/// @brief 运行下一个
	/// @return 成功返回 true
	virtual bool runNextNode( );
	/// @brief 运行剩余
	/// @return 成功返回 true
	virtual bool runResidueNode( );
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
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
