#ifndef BEGINNODEEDITOR_H_H_HEAD__FILE__
#define BEGINNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class QVBoxLayout;
class BeginNodeItem;
class NodeRefLinkInfo;
class BeginNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	NodeRefLinkInfo *beginNodeRefLinkInfo;
	std::vector< NodeRefLinkInfo * > beginNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > processNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > endNodeRefLinkVector;
	QWidget* mainWidget;
	QVBoxLayout* mainLayout;
	BeginNodeItem *beginItem;
	BeginNodeItem *processItem;
	BeginNodeItem *endItem;
public:
	BeginNodeEditor( NodeInfoWidget *parent );
	void * getVarPtr( ) const override;
	const std::type_info & getVarType( ) const override;
	void clearVar( ) override;
	~BeginNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
Q_SIGNALS:
	void clickNodeItem( Node *click_node );
};

#endif // BEGINNODEEDITOR_H_H_HEAD__FILE__
