#ifndef STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class StringCreateUnityNode;
class StringCreateUnityNodeEditorScrollArea;
class StringCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	StringCreateUnityNode *createBinNode;
	StringCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	QString *bindVarPtr;
	QString buffValue;
protected:
	virtual void valueChange( QString new_value );
public:
	StringCreateUnityNodeEditorWidget( StringCreateUnityNode *create_bin_node, QString *bind_var_ptr );
	~StringCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
	
protected:
	void okButtonEvent( ) override;
};

#endif // STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
