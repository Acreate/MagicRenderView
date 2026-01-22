#ifndef STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class StringCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class StringCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNode *createBinNode;
	StringCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint8_t *bindVarPtr;
	uint8_t buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	StringCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr );
	~StringCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
	
protected:
	void okButtonEvent( ) override;
};

#endif // STRINGCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
