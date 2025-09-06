#ifndef NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
#define NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class NodeRunSequenceWidget;
class NodeControlItemWidge : public QWidget {
	Q_OBJECT;
protected:
	NodeRunSequenceWidget* nodeRunSequenceWidget;
public:
	
	NodeControlItemWidge( NodeRunSequenceWidget * node_run_sequence_widget );
};

#endif // NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
