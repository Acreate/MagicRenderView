#ifndef NODEITEMINFO_H_H_HEAD__FILE__
#define NODEITEMINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class QMenu;
class NodeItem;
class NodeItemInfo : public QObject {
	Q_OBJECT;
private:
	friend class NodeDirector;
protected:
	NodeItem *nodeItem;
	QMenu *manageMenu;
public:
	~NodeItemInfo( ) override;
	NodeItemInfo( NodeItem *node_item );
	virtual QMenu * getManageMenu( ) const { return manageMenu; }
	virtual NodeItem * getNodeItem( ) const { return nodeItem; }
Q_SIGNALS:
	void releaseThis( NodeItemInfo *release_ptr );
};

#endif // NODEITEMINFO_H_H_HEAD__FILE__
