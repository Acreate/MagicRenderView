#ifndef NODEITEMINFO_H_H_HEAD__FILE__
#define NODEITEMINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

namespace nodeItemEnum {
	enum class Node_Item_Type;
}
class QMenu;
class NodeItem;
class NodeItemInfo : public QObject {
	Q_OBJECT;
private:
	friend class NodeItemBuilderModule;
	friend class NodeItemBuilderObj;
	friend class NodeDirector;
	friend class NodeDirectorStack;
	friend class StartNodeInfoWidget;
	friend class NodeItemInfoVector;
protected:
	NodeItem *nodeItem;
	QMenu *manageMenu;
	std_vector< NodeItemInfo * > outputNodeItemVector;
	std_vector< NodeItemInfo * > inputNodeItemInfoVector;
protected:
	NodeItemInfo( NodeItem *node_item );
public:
	~NodeItemInfo( ) override;
	virtual QMenu * getManageMenu( ) const { return manageMenu; }
	virtual NodeItem * getNodeItem( ) const { return nodeItem; }
	/// @brief 添加输入引用
	/// @param output_ref_ptr 依赖目标
	/// @return 成功返回 true
	virtual bool appendOutputNodeItemInfo( NodeItemInfo *output_ref_ptr );
	/// @brief 删除输入引用
	/// @param output_ref_ptr 依赖节点
	/// @return 卸载成功返回 true
	virtual bool removeOutputNodeItemInfo( NodeItemInfo *output_ref_ptr );
	/// @brief 检查整个输入引用循环，如果依赖循环当中存在目标，则返回 true
	/// @param output_ref_ptr 检查的目标
	/// @return 存在，返回 true
	virtual bool inOutputNodeItemInfo( NodeItem *output_ref_ptr ) const;
	/// @brief 检查整个输入引用循环，如果依赖循环当中存在目标，则返回 true
	/// @param output_ref_ptr 检查的目标
	/// @return 存在，返回 true
	virtual bool inOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) const;
	/// @brief 引用依赖节点
	/// @param input_ref_ptr 依赖目标
	/// @return 成功返回 true
	virtual bool appendInputNodeItemInfo( NodeItemInfo *input_ref_ptr );
	/// @brief 卸载依赖节点
	/// @param input_ref_ptr 依赖节点
	/// @return 卸载成功返回 true
	virtual bool removeInputNodeItemInfo( NodeItemInfo *input_ref_ptr );
	/// @brief 检查整个依赖循环，如果依赖循环当中存在目标，则返回 true
	/// @param input_ref_ptr 检查的目标
	/// @return 存在，返回 true
	virtual bool inInputNodeItemInfo( NodeItem *input_ref_ptr ) const;
	/// @brief 检查整个依赖循环，如果依赖循环当中存在目标，则返回 true
	/// @param input_ref_ptr 检查的目标
	/// @return 存在，返回 true
	virtual bool inInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) const;
	/// @brief 获取节点类型
	/// @param result 类型
	/// @return 失败返回 false
	virtual bool getNodeItemType( nodeItemEnum::Node_Item_Type &result );
	virtual const std_vector< NodeItemInfo * > & getOutputNodeItemVector( ) const { return outputNodeItemVector; }
	virtual const std_vector< NodeItemInfo * > & getInputNodeItemVector( ) const { return inputNodeItemInfoVector; }

	// 本对象触发信号
Q_SIGNALS:
	void releaseThisPtr( NodeItemInfo *release_ptr );
	void runNodeItemInfo( NodeItemInfo *run_node_item_ptr );
	void requestNodeItemInfoConverVar( NodeItemInfo *left_node_item_ptr, NodeItemInfo *right_node_item_ptr );
	void nodeItemInfoRefChangeInputNodeItem( NodeItemInfo *node_item_info );
	void nodeItemInfoRefChangeOutputNodeItem( NodeItemInfo *node_item_info );
};

class NodeItemInfoVector {
public:
	/// @brief 移动对象到指定位置
	/// @param node_item_info_array_ptr 操作数组
	/// @param inster_node_item_info_source_point 拷贝位置
	/// @param inster_node_item_info_target_point 覆盖位置
	static void moveNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_source_point, const size_t &inster_node_item_info_target_point );
	/// @brief 格式化输出到字符串
	/// @param node_item_info 格式化数组起始地址
	/// @param count 数组个数
	/// @param join_string 拼接字符串
	/// @return 格式化好的字符串
	static QString formatNodeInfoPath( const NodeItemInfo *const*node_item_info, const size_t &count, const QString &join_string );
	/// @brief 填充数据
	/// @param source_node_item_info_array_ptr 检查填充数组
	/// @param source_node_item_info_array_count 检查填充数组个数
	/// @param target_node_item_info_array_ptr 被填充的数组
	/// @param target_node_item_info_array_count 被填充的最大数量
	/// @param fill_check_function 填充条件
	/// @return 填充个数
	static size_t fillNodeItemInfoVector( NodeItemInfo **source_node_item_info_array_ptr, const size_t &source_node_item_info_array_count, NodeItemInfo **target_node_item_info_array_ptr, const size_t &target_node_item_info_array_count, const std_function< bool( NodeItemInfo *check ) > &fill_check_function );
	/// @brief 编译节点序列，使节点按照依赖实现返回顺序序列
	/// @param start_node_item_info_vector 返回依赖序列
	/// @param result_run_node_item_info_vector 编译节点序列
	/// @param result_first_error_node_item_info_ptr
	/// @return 失败返回 false
	static bool builderNodeItemVector( const std_vector< NodeItemInfo * > &start_node_item_info_vector, std_vector< NodeItemInfo * > &result_run_node_item_info_vector, const NodeItemInfo *&result_first_error_node_item_info_ptr );
	/// @brief 填充输出节点到指定序列当中，没有返回 false
	/// @param node_item_info 目标节点
	/// @param result_out_node_item_info_ptr 填充目标
	/// @return 不存在输出返回 false
	static bool fillOutputNodeItemAtVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_out_node_item_info_ptr );
	/// @brief 填充输入节点到指定序列当中，没有返回 false
	/// @param node_item_info 目标节点
	/// @param result_in_node_item_info_ptr 填充目标
	/// @return 不存在输入返回 false
	static bool fillInputNodeItemAtVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_in_node_item_info_ptr );
	/// @brief 检查数组依赖是否正确，返回第一个数组当中找不到依赖的节点
	/// @param runNodeItemInfoArrayPtr 检查数组
	/// @param currentVectorCount 数组个数
	/// @return 第一个找不到依赖的节点
	static const NodeItemInfo * checkNodeItemBuilderVector( const NodeItemInfo *const*runNodeItemInfoArrayPtr, const size_t &currentVectorCount );
	/// @brief 根据依赖进行排序，尾部依赖前部
	/// @param node_item_info_array_ptr 排序数组
	/// @param inster_node_item_info_count 排序个数
	/// @return 排序个数，返回可能小于排序个数，因为排序存在未知依赖，这是节点不在排序列表当中
	static size_t sortNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_count );
};

#endif // NODEITEMINFO_H_H_HEAD__FILE__
