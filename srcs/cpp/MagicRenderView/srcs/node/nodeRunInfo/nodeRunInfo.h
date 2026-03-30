#ifndef NODERUNINFO_H_H_HEAD__FILE__
#define NODERUNINFO_H_H_HEAD__FILE__

#include <QObject>
class NodeRunInfoData;
class NodeRunInfoDataOnlyRead;
class NodeRunInfoDataEditor;
namespace NodeEnum {
	enum class NodeType;
	enum class ErrorType;
	enum class AdviseType;
}
class Application;
class PrinterDirector;
class Node;
class NodeDirector;
class SrackInfo;
class NodeRunInfo : public QObject {
	Q_OBJECT;
protected:
	Application *applicationPtr;
	PrinterDirector *printerDirector;
	NodeDirector *nodeDirectorPtr;
	NodeRunInfoData *nodeRunInfoDataPtr;
	NodeRunInfoData *nodeRunInfoDataImagePtr;
protected:
	virtual NodeRunInfoDataEditor * getNodeRunInfoDataEditor( ) const;
	virtual NodeRunInfoDataOnlyRead * getNodeRunInfoDataOnlyRead( ) const;
	virtual NodeRunInfoData * getNodeRunInfoData( ) const;
	virtual void setNodeRunInfoData( NodeRunInfoData *new_node_run_info_data );

	virtual NodeRunInfoDataEditor * getNodeRunInfoDataEditorImage( ) const;
	virtual NodeRunInfoDataOnlyRead * getNodeRunInfoDataOnlyReadImage( ) const;
	virtual NodeRunInfoData * getNodeRunInfoDataImage( ) const;
	virtual void setNodeRunInfoDataImage( NodeRunInfoData *new_node_run_info_data_image );

	virtual void appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count );
	virtual void appendBuilderNode( Node *append_node_unity );
	virtual void removeBuilderNode( Node *append_node_unity );
	/// @brief 编译实例
	/// @return 失败返回 false
	virtual bool builderRunInstance( );
	/// @brief 到下一帧
	/// @return 成功返回 true
	virtual bool toNextFrame( );
	/// @brief 检查是否存在编译节点
	/// @param check_node_ptr 检查的节点指针
	/// @return 不存在返回 false
	virtual bool hasBuilderNode( const Node *check_node_ptr );
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
public:
	NodeRunInfo( );
	~NodeRunInfo( ) override;
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
};

#endif // NODERUNINFO_H_H_HEAD__FILE__
