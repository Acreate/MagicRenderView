#ifndef BINGENERATENODEWIDGET_H_H_HEAD__FILE__
#define BINGENERATENODEWIDGET_H_H_HEAD__FILE__

#include "../../nodeInfoWidget.h"

class BinGenerateNodeEditor;
class BinGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	BinGenerateNodeEditor *binGenerateNodeEditor;
public:
	BinGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // BINGENERATENODEWIDGET_H_H_HEAD__FILE__
