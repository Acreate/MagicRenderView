#ifndef CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class CharCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class CharCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNode *createBinNode;
	CharCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint8_t *bindVarPtr;
	uint8_t buffValue;
protected:
	virtual void valueChange( uint8_t new_value );
public:
	CharCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr );
	~CharCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
