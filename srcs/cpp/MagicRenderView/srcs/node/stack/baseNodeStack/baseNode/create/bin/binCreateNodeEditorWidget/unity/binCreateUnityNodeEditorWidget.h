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
public:
	BinCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node );
	~BinCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
};

#endif // BINCREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
