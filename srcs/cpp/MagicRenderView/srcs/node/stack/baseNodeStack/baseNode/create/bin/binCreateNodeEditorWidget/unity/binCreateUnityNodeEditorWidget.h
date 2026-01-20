#ifndef BINCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define BINCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class BinCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNode *createBinNode;
	BinCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint8_t *bindVarPtr;
	uint8_t buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	BinCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr );
	~BinCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
	
protected:
	void okButtonEvent( ) override;
};

#endif // BINCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
