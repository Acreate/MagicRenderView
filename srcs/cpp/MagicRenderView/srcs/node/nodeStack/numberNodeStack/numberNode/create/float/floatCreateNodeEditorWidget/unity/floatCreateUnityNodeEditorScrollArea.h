#ifndef FLOATCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define FLOATCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class DoubleValueValidatorWidget;
class ValidatorWidget;
class QVBoxLayout;
class FloatCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class FloatCreateUnityNodeEditorWidget;
protected:
	double currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
	DoubleValueValidatorWidget *doubleValueValidatorWidget;
protected:
	virtual void appendValidatorWidget( ValidatorWidget *append_ptr );
protected Q_SLOTS:
	void overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt );
	void currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr );
	void currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr );
protected:
	FloatCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, double current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~FloatCreateUnityNodeEditorScrollArea( ) override;
	virtual double getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( double current_var );

Q_SIGNALS:
	void editingFinished_Signal( double var );
};
#endif // FLOATCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
