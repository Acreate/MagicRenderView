#ifndef NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../items/nodeRunFunctionSequenceItem.h"

class NodeRunSequenceItemFunctionWidget : public QWidget {
	Q_OBJECT;
protected:
	 NodeRunFunctionSequenceItem *nodeRunFunctionSequenceItem ;
public:
	NodeRunSequenceItemFunctionWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item );
};

#endif // NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
