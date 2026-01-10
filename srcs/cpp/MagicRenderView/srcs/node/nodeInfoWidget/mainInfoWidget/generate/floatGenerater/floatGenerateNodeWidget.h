#ifndef FLOATGENERATENODEWIDGET_H_H_HEAD__FILE__
#define FLOATGENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInfoWidget.h"

class FloatGenerateNodeEditor;
class FloatGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	FloatGenerateNodeEditor *floatGenerateNodeEditor;
public:
	FloatGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // FLOATGENERATENODEWIDGET_H_H_HEAD__FILE__
