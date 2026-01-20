#ifndef BINDECIMALEDITORWIDGET_H_H_HEAD__FILE__
#define BINDECIMALEDITORWIDGET_H_H_HEAD__FILE__
#include "../changeBinValueWidget.h"

class QLabel;
class QLineEdit;
class BinDecimalEditorWidget : public ChangeBinValueWidget {
	Q_OBJECT;
protected:
	QLabel* title;
	QLineEdit * decEditor;
	qsizetype maxLen;
protected:
	virtual void valueChanged_Slot(const QString& text);
public:
	BinDecimalEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	void updateValue( uint8_t new_value ) override;
};


#endif // BINDECIMALEDITORWIDGET_H_H_HEAD__FILE__
