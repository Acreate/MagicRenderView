#ifndef JUMPNODEWIDGET_H_H_HEAD__FILE__
#define JUMPNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class JumpNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	JumpNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
};

#endif // JUMPNODEWIDGET_H_H_HEAD__FILE__
