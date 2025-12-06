#ifndef GENERATENODEWIDGET_H_H_HEAD__FILE__
#define GENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class GenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	std::vector< void * > generateVarVector;
public:
	GenerateNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
	size_t releaseVar( ) override;
	size_t clearVarPtr( ) override;
protected:
	void okButtonEvent( ) override { }
	void cancelButtonEvent( ) override { }
};

#endif // GENERATENODEWIDGET_H_H_HEAD__FILE__
