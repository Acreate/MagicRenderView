#ifndef COLORCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define COLORCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class ColorCreateUnityNodeEditorScrollArea;
class ColorCreateUnityNode;
class ColorCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	ColorCreateUnityNode *createBinNode;
	ColorCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	QColor *bindVarPtr;
	QColor buffValue;
protected:
	virtual void valueChange( QColor new_value );
public:
	ColorCreateUnityNodeEditorWidget( ColorCreateUnityNode *create_bin_node, QColor *bind_var_ptr );
	~ColorCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};
#endif // COLORCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
