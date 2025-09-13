#ifndef NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../items/nodeRunFunctionSequenceItem.h"

class NodeRunSequenceItemFunctionWidget : public QWidget {
	Q_OBJECT;
public:
	friend class NodeRunSequenceWidget;
protected:
	 NodeRunFunctionSequenceItem *nodeRunFunctionSequenceItem ;
public:
	NodeRunSequenceItemFunctionWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void showEvent( QShowEvent *event ) override;
	void hideEvent( QHideEvent *event ) override;
};

#endif // NODERUNSEQUENCEITEMFUNCTIONWIDGET_H_H_HEAD__FILE__
