#ifndef EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#define EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class VarDirector;
class NodeRefLinkInfo;
class Node;
class NodeInfoWidget;
class EditorNodeInfoScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	NodeInfoWidget *parentNodeInfoWidget;
	VarDirector *parentVarDirector;
	Node *currentNode;
	QScrollBar *hScrollAreaBar;
	QScrollBar *vScrollAreaBar;
protected:
	virtual void releaseResource( );
public:
	EditorNodeInfoScrollArea( NodeInfoWidget *parent );
	virtual bool initNode( Node *init_node );
	virtual Node * getCurrentNode( ) const { return currentNode; }
	virtual NodeInfoWidget * getParentNodeInfoWidget( ) const { return parentNodeInfoWidget; }
protected:
	void hideEvent( QHideEvent *event ) override;
	bool eventFilter( QObject *event_obj_ptr, QEvent *event_type ) override;
};

#endif // EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
