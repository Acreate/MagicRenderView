#ifndef NODEITEMBUILDERMODE_H_H_HEAD__FILE__
#define NODEITEMBUILDERMODE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class NodeItemInfo;
class NodeItemBuilderMode {
public:
	/// @brief 生成运行模块
	/// @param start_node_item_info_vector 开始节点
	/// @param end_node_item_info_vector 结束节点
	/// @param normal_node_item_info_vector 常规节点
	/// @return 模块列表指针对象
	static std_vector_shared_unity_shared< NodeItemBuilderMode > generateNodeItemBuilderModeVector( const std_vector< NodeItemInfo * > &start_node_item_info_vector, const std_vector< NodeItemInfo * > &end_node_item_info_vector, const std_vector< NodeItemInfo * > &normal_node_item_info_vector );
	/// @brief 生成运行模块
	/// @param node_item_info_vector 所有的有效模块
	/// @return 模块列表指针对象
	static std_vector_shared_unity_shared< NodeItemBuilderMode > generateNodeItemBuilderModeVector( const std_vector< NodeItemInfo * > &node_item_info_vector );
protected:
	std_vector<NodeItemInfo *> runNodeItemInfoVector;
protected:
	NodeItemBuilderMode( ) { }
public:
	virtual ~NodeItemBuilderMode() = default;
	virtual bool getRunNodeItems( std_vector< NodeItemInfo * > &result_current_run_info_vector );
};

#endif // NODEITEMBUILDERMODE_H_H_HEAD__FILE__
