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

protected:
	QScrollBar *scrollBar;
	QLabel *scrollBarTitile;
	QLabel *valueTitile;
	QVBoxLayout *mainLayout;
	QWidget *scrollWidget;
	QHBoxLayout *scrollWidgetLayout;
public:
	ScrollValueChangeWidget( QWidget *parent );
	virtual void scrollToPoint( double value, double min_var, double max_var );
	virtual void scrollToTitleValue( uint64_t value );
	virtual void scrollToTitleValue( int64_t value );
Q_SIGNALS:
	void value_change_signal( int curren_scroll_bar_point );
};
#endif // SCROLLVALUECHANGEWIDGET_H_H_HEAD__FILE__
