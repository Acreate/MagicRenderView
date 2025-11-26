#ifndef DRAWNODEWIDGET_H_H_HEAD__FILE__
#define DRAWNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Node;
class Application;
class NodeDirector;
class DrawNodeWidget : public QWidget {
	Q_OBJECT;
	friend class MainWidget;
	friend class MainWindow;
protected:
	Application *appInstancePtr;
	NodeDirector *nodeDirector;
	QPoint menuPopPoint;
	std::vector< Node * > nodeVector;
protected:
	virtual void appendVector( Node *append_node );
	virtual void removeVector( Node *remove_node );
	virtual void raiseNode( Node *raise_node );
public:
	DrawNodeWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~DrawNodeWidget( ) override;
	virtual bool addNode( Node *add_node );
	virtual const QPoint & getMenuPopPoint( ) const { return menuPopPoint; }
};

#endif // DRAWNODEWIDGET_H_H_HEAD__FILE__
