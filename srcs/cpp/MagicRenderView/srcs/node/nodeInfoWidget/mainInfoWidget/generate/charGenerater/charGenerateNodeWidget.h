#ifndef CHARGENERATENODEWIDGET_H_H_HEAD__FILE__
#define CHARGENERATENODEWIDGET_H_H_HEAD__FILE__

#include "../../nodeInfoWidget.h"


class CharGenerateNodeEditor;
class CharGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	CharGenerateNodeEditor *charGenerateNodeEditor;
public:
	CharGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // CHARGENERATENODEWIDGET_H_H_HEAD__FILE__
