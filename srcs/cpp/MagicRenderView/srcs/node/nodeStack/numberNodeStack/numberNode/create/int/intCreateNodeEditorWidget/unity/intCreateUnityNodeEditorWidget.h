#ifndef INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class IntCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class IntCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNode *createBinNode;
	IntCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint8_t *bindVarPtr;
	uint8_t buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	IntCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr );
	~IntCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // INTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
