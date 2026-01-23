#ifndef FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class FloatCreateUnityNode;
class FloatCreateUnityNodeEditorScrollArea;
class FloatCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	FloatCreateUnityNode *createBinNode;
	FloatCreateUnityNodeEditorScrollArea *binCreateUnityNodeScrollArea;
	double *bindVarPtr;
	double buffValue;
protected:
	virtual void valueChange( double new_value );
public:
	FloatCreateUnityNodeEditorWidget( FloatCreateUnityNode *create_bin_node, double *bind_var_ptr );
	~FloatCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
};

#endif // FLOATCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
