#ifndef INTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define INTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class Int64DecValidatorWidget;
class ValidatorWidget;
class QVBoxLayout;
class IntCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class IntCreateUnityNodeEditorWidget;
protected:
	union Type64Bin {
		qlonglong longLong;
		qulonglong ulongLong;
	};
	int64_t currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
	Int64DecValidatorWidget *int64DecValidatorWidget;
protected:
	virtual void appendValidatorWidget( ValidatorWidget *append_ptr );
protected Q_SLOTS:
	void overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt );
	void currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr );
	void currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr );
	void intOverEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt );
protected:
	IntCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, int64_t current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~IntCreateUnityNodeEditorScrollArea( ) override;
	virtual int64_t getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( int64_t current_var );

Q_SIGNALS:
	void editingFinished_Signal( int64_t var );
};
#endif // INTCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
