#ifndef INTGENERATENODEWIDGET_H_H_HEAD__FILE__
#define INTGENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class IntGenerateNodeEditor;
class IntGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	IntGenerateNodeEditor *intGenerateNodeEditor;
public:
	IntGenerateNodeWidget(  );
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // INTGENERATENODEWIDGET_H_H_HEAD__FILE__
