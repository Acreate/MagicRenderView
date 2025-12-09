#ifndef JUMPNODEEDITOR_H_H_HEAD__FILE__
#define JUMPNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class JumpNodeWidgetItem;
class QVBoxLayout;
class NodeRefLinkInfo;
class JumpNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	std::vector< NodeRefLinkInfo * > beginNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > processNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	std::vector< JumpNodeWidgetItem * > unionJumpNodeVector;
protected:
	void releaseResource( ) override;
	virtual bool createJumpItem( NodeRefLinkInfo *node_ref_link_info );
public:
	JumpNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
};

#endif // JUMPNODEEDITOR_H_H_HEAD__FILE__
