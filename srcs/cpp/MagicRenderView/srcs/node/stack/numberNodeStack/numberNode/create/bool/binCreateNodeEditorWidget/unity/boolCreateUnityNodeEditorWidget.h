#ifndef BOOLCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define BOOLCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class BoolCreateUnityNodeEditorScrollArea;
class BoolCreateUnityNode;
class BoolCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BoolCreateUnityNode *createBoolNode;
	BoolCreateUnityNodeEditorScrollArea *boolCreateUnityNodeEditorScrollArea;
	bool *bindVarPtr;
	bool buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	BoolCreateUnityNodeEditorWidget( BoolCreateUnityNode *create_bin_node, bool *bind_var_ptr );
	~BoolCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // BOOLCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
