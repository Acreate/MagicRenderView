#ifndef ENDNODEWIDGET_H_H_HEAD__FILE__
#define ENDNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class EndNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	EndNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
};

#endif // ENDNODEWIDGET_H_H_HEAD__FILE__
