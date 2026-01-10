#ifndef COLORGENERATENODEWIDGET_H_H_HEAD__FILE__
#define COLORGENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInfoWidget.h"


class ColorGenerateNodeEditor;
class ColorGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	ColorGenerateNodeEditor *charGenerateNodeEditor;
public:
	ColorGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // COLORGENERATENODEWIDGET_H_H_HEAD__FILE__
