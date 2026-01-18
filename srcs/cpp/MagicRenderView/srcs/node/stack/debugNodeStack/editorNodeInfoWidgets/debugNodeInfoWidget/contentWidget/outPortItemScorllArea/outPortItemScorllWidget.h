#ifndef OUTPORTITEMSCORLLWIDGET_H_H_HEAD__FILE__
#define OUTPORTITEMSCORLLWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class QVBoxLayout;
class OutPortItemWidget;
class OutputPort;
class OutPortItemScorllWidget : public QWidget {
	Q_OBJECT;
protected:
	std::list<OutPortItemWidget*> outputPortItemList;
	QVBoxLayout* mainLayout;
public:
	OutPortItemScorllWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~OutPortItemScorllWidget( ) override;
	virtual bool appendOutputItem( OutputPort *output_port_ptr, const QString &msg );
};

#endif // OUTPORTITEMSCORLLWIDGET_H_H_HEAD__FILE__
