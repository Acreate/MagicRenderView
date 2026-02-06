#ifndef DEBUGNODECONTENTTOOLSWIDGET_H_H_HEAD__FILE__
#define DEBUGNODECONTENTTOOLSWIDGET_H_H_HEAD__FILE__


#include <QWidget>

class SrackInfo;
class BuilderDirector;
class QVBoxLayout;
class QPushButton;
class Node;
class DebugNodeContentToolsWidget : public QWidget {
	Q_OBJECT;
protected:
	Node *targetNode;
	QPushButton *runBtn;
	QVBoxLayout *mainLayout;
	BuilderDirector *builderDirector;
protected:
	virtual void RunBtnClick( );
	virtual void createNodeRunInfoBtnClickInfoAction( );
	virtual void releaseNodeRunInfoBtnClickInfoAction( );
public:
	virtual void setTargetNode( Node *target_node );
	DebugNodeContentToolsWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
Q_SIGNALS:
	void click_builder_target_signal( Node *target_node );
};

#endif // DEBUGNODECONTENTTOOLSWIDGET_H_H_HEAD__FILE__
