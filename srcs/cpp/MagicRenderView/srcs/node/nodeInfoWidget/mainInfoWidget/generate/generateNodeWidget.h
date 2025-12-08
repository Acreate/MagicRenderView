#ifndef GENERATENODEWIDGET_H_H_HEAD__FILE__
#define GENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class GenerateNodeEditor;
class GenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	std::vector< void * > generateVarVector;
	GenerateNodeEditor *generateNodeEditor;
public:
	GenerateNodeWidget( MainWindow *parent );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
protected:
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // GENERATENODEWIDGET_H_H_HEAD__FILE__
