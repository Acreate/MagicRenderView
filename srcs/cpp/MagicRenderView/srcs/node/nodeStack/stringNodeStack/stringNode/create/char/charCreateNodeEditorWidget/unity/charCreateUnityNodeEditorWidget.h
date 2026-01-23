#ifndef CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class CharCreateUnityNode;
class CharCreateUnityNodeEditorScrollArea;
class BinCreateUnityNodeEditorScrollArea;
class BinCreateUnityNode;
class CharCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	CharCreateUnityNode *createBinNode;
	CharCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	QChar *bindVarPtr;
	QChar buffValue;
protected:
	virtual void valueChange( QChar new_value );
public:
	CharCreateUnityNodeEditorWidget( CharCreateUnityNode *create_bin_node, QChar *bind_var_ptr );
	~CharCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // CHARCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
