#ifndef UINTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define UINTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class UIntCreateUnityNode;
class UIntCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class UIntCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	UIntCreateUnityNode *createBindNode;
	UIntCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	uint64_t *bindVarPtr;
	uint64_t buffValue;
protected:
	virtual void valueChange( uint64_t new_value );
public:
	UIntCreateUnityNodeEditorWidget( UIntCreateUnityNode *create_bin_node, uint64_t *bind_var_ptr );
	~UIntCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // UINTCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
