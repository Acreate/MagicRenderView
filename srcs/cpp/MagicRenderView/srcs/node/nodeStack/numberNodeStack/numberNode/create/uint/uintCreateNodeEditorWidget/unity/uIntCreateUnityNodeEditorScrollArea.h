#ifndef UINTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define UINTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class UIntCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class UIntCreateUnityNodeEditorWidget;
protected:
	uint64_t currentVar;
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
	UIntCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint64_t current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~UIntCreateUnityNodeEditorScrollArea( ) override;
	virtual uint64_t getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( uint64_t current_var );

Q_SIGNALS:
	void editingFinished_Signal( uint64_t var );
};
#endif // UINTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
