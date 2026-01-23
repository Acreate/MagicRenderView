#ifndef STRINGCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define STRINGCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class StringCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class StringCreateUnityNodeEditorWidget;
protected:
	uint8_t currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget* currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
protected:
	virtual void appendValidatorWidget( ValidatorWidget *append_ptr );
protected Q_SLOTS:
	void overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt );
	void currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr );
	void currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr );
protected:
	StringCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~StringCreateUnityNodeEditorScrollArea( ) override;
	virtual uint8_t getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( uint8_t current_var );

Q_SIGNALS:
	void editingFinished_Signal( uint8_t var );
};
#endif // STRINGCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
