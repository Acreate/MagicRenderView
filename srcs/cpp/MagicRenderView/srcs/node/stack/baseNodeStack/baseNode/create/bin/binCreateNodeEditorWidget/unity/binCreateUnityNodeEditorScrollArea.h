#ifndef BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class QLineEdit;
class BinCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class BinCreateUnityNodeEditorWidget;
protected:
	uint8_t currentVar;
	QWidget *mainWidget;
	QLineEdit *lineEdit;
protected Q_SLOTS:
	void editingFinished_Slot( );
protected:
	BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~BinCreateUnityNodeEditorScrollArea( ) override;
Q_SIGNALS:
	void editingFinished_Signal( uint8_t var );
};

#endif // BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
