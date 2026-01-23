#ifndef DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
#define DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
#include <QWidget>
class DebugNodeContentToolsWidget;
class OutPortItemScrollArea;
class OutPortItemScrollWidget;
class DebugInfoNode;
class OutputPort;

class Node;
class DebugNodeContentWidget : public QWidget {
	Q_OBJECT;
protected:
	DebugNodeContentToolsWidget *tool;
	OutPortItemScrollArea *outputItemScrollArea;
	OutPortItemScrollWidget *outPortItemScrollWidget;
public:
	DebugNodeContentWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	virtual bool init( DebugInfoNode *node );
	virtual bool updateLayout( );
	virtual OutPortItemScrollWidget * getOutPortItemScrollWidget( ) const { return outPortItemScrollWidget; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
Q_SIGNALS:
	void click_builder_target_signal( Node *target_node );
};

#endif // DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
