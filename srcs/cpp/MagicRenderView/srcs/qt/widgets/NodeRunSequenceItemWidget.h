#ifndef NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class NodeRunFunctionSequenceItem;
class NodeRunSequenceWidget;
class NodeRunSequenceItemWidget : public QWidget {
	Q_OBJECT;
protected:
	int minWidth;
	int minHeight;
	NodeRunFunctionSequenceItem *nodeRunFunctionSequenceItem;
public:
	NodeRunSequenceItemWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item );
protected:
	void paintEvent( QPaintEvent *event ) override;
public:
	virtual void updateRenderItems( );
	virtual int getMinWidth( ) const { return minWidth; }
	virtual int getMinHeight( ) const { return minHeight; }
Q_SIGNALS:
	void sequenceItemUpdate( NodeRunSequenceItemWidget *send_widget_ptr );
};

#endif // NODERUNSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
