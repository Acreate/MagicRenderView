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
	friend class NodeItemBuilderObj;
	friend class NodeDirector;
	friend class NodeDirectorStack;
	friend class StartNodeInfoWidget;
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

#endif // NODEITEMINFO_H_H_HEAD__FILE__
