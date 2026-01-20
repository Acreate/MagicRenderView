#ifndef CHANGEBINVALUEWIDGET_H_H_HEAD__FILE__
#define CHANGEBINVALUEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class BinCreateUnityNodeEditorScrollArea;
class ChangeBinValueWidget : public QWidget {
	Q_OBJECT;
protected:
	BinCreateUnityNodeEditorScrollArea *binCreateUnityNodeEditorScrollArea;
	uint8_t binOr;
public:
	ChangeBinValueWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	virtual void updateValue( uint8_t new_value ) = 0;
Q_SIGNALS:
	void value_change_signal( ChangeBinValueWidget *send_ptr, uint8_t new_value );
};

#endif // CHANGEBINVALUEWIDGET_H_H_HEAD__FILE__
