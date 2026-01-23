#ifndef CHARCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define CHARCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class CharCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class CharCreateUnityNodeEditorWidget;
protected:
	QChar currentVar;
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
	CharCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, QChar current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~CharCreateUnityNodeEditorScrollArea( ) override;
	virtual QChar getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( QChar current_var );

Q_SIGNALS:
	void editingFinished_Signal( QChar var );
};
#endif // CHARCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
