#ifndef BINSCROLLBAREDITORWIDGET_H_H_HEAD__FILE__
#define BINSCROLLBAREDITORWIDGET_H_H_HEAD__FILE__
#include "../changeBinValueWidget.h"

class QScrollBar;
class QLabel;
class QVBoxLayout;
class QWidget;
class QHBoxLayout;
class BinScrollBarEditorWidget : public ChangeBinValueWidget {
	Q_OBJECT;
protected:
	QScrollBar *scrollBar;
	QLabel *scrollBarTitile;
	QLabel *valueTitile;
	QVBoxLayout *mainLayout;
	QWidget *scrollWidget;
	QHBoxLayout *scrollWidgetLayout;
	qsizetype maxLen;
protected:
	virtual void scrollValueChange( int value );
public:
	BinScrollBarEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area );
	void updateValue( uint8_t new_value ) override;
};

#endif // BINSCROLLBAREDITORWIDGET_H_H_HEAD__FILE__
