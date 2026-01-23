#ifndef INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class IntCreateUnityNode;
class IntCreateUnityNodeEditorScrollArea;
class IntCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	IntCreateUnityNode *createBinNode;
	IntCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	int64_t *bindVarPtr;
	int64_t buffValue;
protected:
	virtual void valueChange( int64_t new_value );
public:
	IntCreateUnityNodeEditorWidget( IntCreateUnityNode *create_bin_node, int64_t *bind_var_ptr );
	~IntCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
