#ifndef BINOCTEDITORWIDGET_H_H_HEAD__FILE__
#define BINOCTEDITORWIDGET_H_H_HEAD__FILE__
#include "../changeBinValueWidget.h"

class QLineEdit;
class QLabel;
class QLabel;
class BinOctEditorWidget : public ChangeBinValueWidget {
	Q_OBJECT;
protected:
	QLabel* title;
	QLineEdit * octEditor;
	qsizetype maxLen;
protected:
	virtual void valueChanged_Slot(const QString& text);
public:
	BinOctEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	void updateValue( uint8_t new_value ) override;
};

#endif // BINOCTEDITORWIDGET_H_H_HEAD__FILE__
