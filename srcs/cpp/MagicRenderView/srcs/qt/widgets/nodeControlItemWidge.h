#ifndef NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
#define NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

#include "nodeRunSequenceWidget.h"

class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunSequenceWidget;
class NodeControlItemWidge : public NodeRunSequenceWidget {
	Q_OBJECT;
protected:
	NodeRunSequenceWidget *nodeRunSequenceWidget;
public:
	NodeControlItemWidge( NodeRunSequenceWidget *node_run_sequence_widget );
};

#endif // NODECONTROLITEMWIDGE_H_H_HEAD__FILE__
