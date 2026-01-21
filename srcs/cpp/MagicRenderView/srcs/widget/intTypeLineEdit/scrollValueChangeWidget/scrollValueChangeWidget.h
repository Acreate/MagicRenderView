#ifndef SCROLLVALUECHANGEWIDGET_H_H_HEAD__FILE__
#define SCROLLVALUECHANGEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QScrollBar;
class QLabel;
class QVBoxLayout;
class QWidget;
class QHBoxLayout;
class ScrollValueChangeWidget : public QWidget {
	Q_OBJECT;
protected:
	QScrollBar *scrollBar;
	QLabel *scrollBarTitile;
	QLabel *valueTitile;
	QVBoxLayout *mainLayout;
	QWidget *scrollWidget;
	QHBoxLayout *scrollWidgetLayout;
	qsizetype maxLen;
	uint8_t binOr;
protected:
	virtual void scrollValueChange( int value );
public:
	ScrollValueChangeWidget( int64_t min_value, size_t max_value, QWidget *parent );
	virtual void updateValue( uint8_t new_value );
Q_SIGNALS:
	void value_change_signal( ScrollValueChangeWidget *send_ptr, uint8_t new_value );
};
#endif // SCROLLVALUECHANGEWIDGET_H_H_HEAD__FILE__
