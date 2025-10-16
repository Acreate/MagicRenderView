#ifndef NODEITEMINFO_H_H_HEAD__FILE__
#define NODEITEMINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class QMenu;
class NodeItem;
class NodeItemInfo : public QObject {
	Q_OBJECT;
private:
	friend class NodeDirector;
protected:
	NodeItem *nodeItem;
	QMenu *manageMenu;
	std_vector< NodeItemInfo * > linkInfoVector;
public:
	~NodeItemInfo( ) override;
	NodeItemInfo( NodeItem *node_item );
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
Q_SIGNALS:
	void releaseThis( NodeItemInfo *release_ptr );
};

#endif // NODEITEMINFO_H_H_HEAD__FILE__
