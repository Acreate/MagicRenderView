#ifndef BINBINEDITORWIDGET_H_H_HEAD__FILE__
#define BINBINEDITORWIDGET_H_H_HEAD__FILE__
#include "../changeBinValueWidget.h"

class QLabel;
class QLineEdit;
class BinBinEditorWidget : public ChangeBinValueWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *binEditor;
	qsizetype maxLen;
protected:
	virtual void valueChanged_Slot( const QString &text );
public:
	BinBinEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	void updateValue( uint8_t new_value ) override;
};

#endif // BINBINEDITORWIDGET_H_H_HEAD__FILE__
