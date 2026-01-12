#ifndef UINTGENERATENODEWIDGET_H_H_HEAD__FILE__
#define UINTGENERATENODEWIDGET_H_H_HEAD__FILE__

#include "../../nodeInfoWidget.h"

class UIntGenerateNodeEditor;
class UIntGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	UIntGenerateNodeEditor *uintGenerateNodeEditor;
public:
	UIntGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // UINTGENERATENODEWIDGET_H_H_HEAD__FILE__
