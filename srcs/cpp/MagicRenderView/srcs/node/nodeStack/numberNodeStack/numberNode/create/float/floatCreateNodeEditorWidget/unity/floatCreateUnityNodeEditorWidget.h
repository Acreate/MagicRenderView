#ifndef FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class FloatCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class FloatCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNode *createBinNode;
	FloatCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint8_t *bindVarPtr;
	uint8_t buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	FloatCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr );
	~FloatCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
	
protected:
	void okButtonEvent( ) override;
};

#endif // FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
