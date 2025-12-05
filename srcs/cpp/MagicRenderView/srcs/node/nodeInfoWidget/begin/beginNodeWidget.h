#ifndef BEGINNODEWIDGET_H_H_HEAD__FILE__
#define BEGINNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class BeginNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	BeginNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
};

#endif // BEGINNODEWIDGET_H_H_HEAD__FILE__
