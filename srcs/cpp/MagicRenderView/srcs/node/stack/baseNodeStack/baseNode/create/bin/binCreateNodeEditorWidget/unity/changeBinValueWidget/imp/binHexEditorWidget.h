#ifndef BINHEXEDITORWIDGET_H_H_HEAD__FILE__
#define BINHEXEDITORWIDGET_H_H_HEAD__FILE__
#include "../changeBinValueWidget.h"

class QLineEdit;
class QLabel;
class BinHexEditorWidget : public ChangeBinValueWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *hexEditor;
	qsizetype maxLen;
protected:
	virtual void valueChanged_Slot( const QString &text );
public:
	BinHexEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	void updateValue( uint8_t new_value ) override;

};

#endif // BINHEXEDITORWIDGET_H_H_HEAD__FILE__
