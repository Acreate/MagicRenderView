#ifndef NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class NodeRunFunctionSequenceItem;
class NodeRunSequenceWidget;
class NodeRunSequenceItemWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeRunSequenceWidget *nodeRunSequenceWidget;
	NodeRunFunctionSequenceItem *nodeRunFunctionSequenceItem;
public:
	NodeRunSequenceItemWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item );
};

#endif // NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
