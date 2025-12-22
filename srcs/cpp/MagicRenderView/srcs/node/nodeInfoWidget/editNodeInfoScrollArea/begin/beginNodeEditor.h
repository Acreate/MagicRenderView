#ifndef BEGINNODEEDITOR_H_H_HEAD__FILE__
#define BEGINNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class QVBoxLayout;
class BeginNodeItem;
class BeginNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	Node *beginNodeRefLinkInfo;
	std::vector< Node * > beginNodeRefLinkVector;
	std::vector< Node * > processNodeRefLinkVector;
	std::vector< Node * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	BeginNodeItem *beginItem;
	BeginNodeItem *processItem;
	BeginNodeItem *endItem;
	NodeInfoWidget *leftWidget;
	NodeInfoWidget *rightWidget;
public:
	BeginNodeEditor( NodeInfoWidget *parent );
	~BeginNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
protected:
	void releaseResource( ) override;
public:
Q_SIGNALS:
	void clickNodeItem( Node *click_node );
};

#endif // BEGINNODEEDITOR_H_H_HEAD__FILE__
