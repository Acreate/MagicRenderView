#ifndef NODERUNFUNCTIONSEQUENCEITEMRNDERWIDGET_H_H_HEAD__FILE__
#define NODERUNFUNCTIONSEQUENCEITEMRNDERWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunFunctionSequenceItem;
class NodeRunSequenceWidget;
class NodeRunFunctionSequenceItemRnderWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeRunSequenceWidget *runSequenceWidget;
	NodeRunFunctionSequenceItem *runFunctionSequenceItem;
public:
	NodeRunFunctionSequenceItemRnderWidget( NodeRunFunctionSequenceItem *run_function_sequence_item );
};

#endif // NODERUNFUNCTIONSEQUENCEITEMRNDERWIDGET_H_H_HEAD__FILE__
