
#ifndef STRINGGENERATENODEWIDGET_H_H_HEAD__FILE__
#define STRINGGENERATENODEWIDGET_H_H_HEAD__FILE__

#include "../../nodeInfoWidget.h"

class StringGenerateNodeEditor;
class StringGenerateNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	std::function< void*( ) > createFunction;
	StringGenerateNodeEditor *stringGenerateNodeEditor;
public:
	StringGenerateNodeWidget(  );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
	void cancelButtonEvent( ) override;
	void okButtonEvent( ) override;
};

#endif // STRINGGENERATENODEWIDGET_H_H_HEAD__FILE__
