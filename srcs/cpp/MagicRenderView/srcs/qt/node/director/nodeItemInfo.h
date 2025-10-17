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
	friend class NodeDirector;
	friend class NodeItemBuilderLink;
	friend class NodeItemBuilderMode;
protected:
	NodeItem *nodeItem;
	QMenu *manageMenu;
	std_vector< NodeItemInfo * > linkInfoVector;
protected:
	NodeItemInfo( NodeItem *node_item );
public:
	~NodeItemInfo( ) override;
	virtual QMenu * getManageMenu( ) const { return manageMenu; }
	virtual NodeItem * getNodeItem( ) const { return nodeItem; }
	/// @brief 引用依赖节点
	/// @param link_target 依赖目标
	/// @return 成功返回 true
	virtual bool linkThis( NodeItemInfo *link_target );
	/// @brief 卸载依赖节点
	/// @param link_target 依赖节点
	/// @return 卸载成功返回 true
	virtual bool unlinkThis( NodeItemInfo *link_target );
	/// @brief 检查整个依赖循环，如果依赖循环当中存在目标，则返回 true
	/// @param link_target 检查的目标
	/// @return 存在，返回 true
	virtual bool inLinkHasNodeItem( NodeItem *link_target ) const;
	/// @brief 检查整个依赖循环，如果依赖循环当中存在目标，则返回 true
	/// @param link_target 检查的目标
	/// @return 存在，返回 true
	virtual bool inLinkHasNodeItem( NodeItemInfo *link_target ) const;
	/// @brief 获取节点类型
	/// @param result 类型
	/// @return 失败返回 false
	virtual bool getNodeItemType( nodeItemEnum::Node_Item_Type &result );
Q_SIGNALS:
	void releaseThis( NodeItemInfo *release_ptr );
};

#endif // NODEITEMINFO_H_H_HEAD__FILE__
