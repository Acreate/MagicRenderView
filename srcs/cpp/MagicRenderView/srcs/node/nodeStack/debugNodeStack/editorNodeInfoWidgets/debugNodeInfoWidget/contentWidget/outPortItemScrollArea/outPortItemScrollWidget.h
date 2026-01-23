#ifndef OUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__
#define OUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QVBoxLayout;
class OutPortItemWidget;
class OutputPort;
class OutPortItemScrollWidget : public QWidget {
	Q_OBJECT;
protected:
	std::list<OutPortItemWidget*> outputPortItemList;
	QVBoxLayout* mainLayout;
public:
	OutPortItemScrollWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~OutPortItemScrollWidget( ) override;
	virtual bool appendOutputItem( OutputPort *output_port_ptr, const QString &msg );
	virtual bool clear();
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // OUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__
