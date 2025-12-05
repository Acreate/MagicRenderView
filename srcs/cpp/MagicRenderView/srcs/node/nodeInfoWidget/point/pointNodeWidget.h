#ifndef POINTNODEWIDGET_H_H_HEAD__FILE__
#define POINTNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class PointNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	PointNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
};

#endif // POINTNODEWIDGET_H_H_HEAD__FILE__
