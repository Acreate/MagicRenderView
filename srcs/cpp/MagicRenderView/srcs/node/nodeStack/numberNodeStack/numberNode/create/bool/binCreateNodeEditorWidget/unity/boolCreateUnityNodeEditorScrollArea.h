#ifndef BOOLCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define BOOLCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class BoolCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class BoolCreateUnityNodeEditorWidget;
protected:
	bool currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
protected:
	virtual void appendValidatorWidget( ValidatorWidget *append_ptr );
protected Q_SLOTS:
	void overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt );
	void currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr );
	void currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr );
protected:
	BoolCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, bool current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~BoolCreateUnityNodeEditorScrollArea( ) override;
	virtual uint8_t getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( uint8_t current_var );

Q_SIGNALS:
	void editingFinished_Signal( uint8_t var );
};
#endif // BOOLCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
