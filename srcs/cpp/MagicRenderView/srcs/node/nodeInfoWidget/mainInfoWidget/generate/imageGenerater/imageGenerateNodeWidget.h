#ifndef IMAGEGENERATENODEWIDGET_H_H_HEAD__FILE__
#define IMAGEGENERATENODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInfoWidget.h"


class ImageGenerateNodeEditor;
class ImageGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	ImageGenerateNodeEditor *charGenerateNodeEditor;
public:
	ImageGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // IMAGEGENERATENODEWIDGET_H_H_HEAD__FILE__
