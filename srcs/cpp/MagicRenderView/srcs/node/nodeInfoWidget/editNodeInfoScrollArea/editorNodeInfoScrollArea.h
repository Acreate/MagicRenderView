#ifndef EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#define EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class Node;
class NodeInfoWidget;
class EditorNodeInfoScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	NodeInfoWidget *parent;
	Node *currentNode;
	QString typeName;
	void *varPtr;
public:
	EditorNodeInfoScrollArea( NodeInfoWidget *parent );
	virtual bool initNode( Node *init_node );
	virtual void * getVarPtr( ) const = 0;
	virtual const std::type_info & getVarType( ) const = 0;
	virtual void clearVar( ) = 0;
	virtual Node * getCurrentNode( ) const { return currentNode; }
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual void * getVarPtr1( ) const { return varPtr; }
	virtual NodeInfoWidget * getParent( ) const { return parent; }
};

#endif // EDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
