#ifndef DRAWNODEWIDGET_H_H_HEAD__FILE__
#define DRAWNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../node/nodeInfo/nodeClickInfo.h"
#include "../node/nodeInfo/nodeRefLinkInfo.h"

class Node;
class Application;
class NodeDirector;
class NodeClickInfo;
class DrawNodeWidget : public QWidget {
	Q_OBJECT;
	friend class MainWidget;
	friend class MainWindow;
	friend class NodeDirector;
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
	virtual bool init( MainWidget *parent );
	virtual bool addNode( Node *add_node );
	virtual const QPoint & getMenuPopPoint( ) const { return menuPopPoint; }
	virtual bool getPointNodeClickInfo( const QPoint &click_point, NodeClickInfo &result_node_click_info );
protected:
	void paintEvent( QPaintEvent *event ) override;
	bool event( QEvent *event ) override;
Q_SIGNALS:
	void release_signal( DrawNodeWidget *release_ptr );
};

#endif // DRAWNODEWIDGET_H_H_HEAD__FILE__
