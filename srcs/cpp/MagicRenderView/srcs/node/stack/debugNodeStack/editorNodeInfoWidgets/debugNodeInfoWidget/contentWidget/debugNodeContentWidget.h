#ifndef DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
#define DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
#include <QWidget>
class DebugInfoNode;
class OutPortItemScorllWidget;
class OutPortItemScorllArea;
class OutputPort;
class DebugNodeConetentToolsWidget;
class Node;
class DebugNodeContentWidget : public QWidget {
	Q_OBJECT;
protected:
	DebugNodeConetentToolsWidget *tool;
	OutPortItemScorllArea *outputItemScorllArea;
	OutPortItemScorllWidget *outPortItemScorllWidget;
public:
	DebugNodeContentWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	virtual bool init( DebugInfoNode *node );
	virtual bool updateLayout( );
	virtual bool appendOutputPort( OutputPort *output_port_ptr, const QString &msg );
Q_SIGNALS:
	void click_builder_target_signal( Node *target_node );
};

#endif // DEBUGNODECONTENTWIDGET_H_H_HEAD__FILE__
