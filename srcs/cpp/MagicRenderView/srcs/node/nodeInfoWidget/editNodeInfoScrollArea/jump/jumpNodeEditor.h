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
	NodeRefLinkInfo *beginNodeRefLinkInfo;
	std::vector< NodeRefLinkInfo * > beginNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > processNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	std::vector< JumpNodeWidgetItem * > unionJumpNodeVector;
	NodeInfoWidget *leftWidget;
	NodeInfoWidget *rightWidget;
protected:
	virtual void releaseResource( );
protected:
	virtual void showNodeInfoWidgetLeft( NodeRefLinkInfo *node_ref_link_info );
	virtual void showNodeInfoWidgetRight( NodeRefLinkInfo *node_ref_link_info );
public:
	JumpNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
protected:
	void hideEvent( QHideEvent *event ) override;
	bool eventFilter( QObject *event_obj_ptr, QEvent *event_type ) override;
};

#endif // JUMPNODEEDITOR_H_H_HEAD__FILE__
