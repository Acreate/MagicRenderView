#ifndef OUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__
#define OUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class OutPortItemScrollWidget;
class OutPortItemWidget;
class OutPortItemScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	OutPortItemScrollWidget* outPortItemScrollWidget;
public:
	OutPortItemScrollArea( QWidget *parent );
	virtual OutPortItemScrollWidget * getOutPortItemScrollWidget( ) const { return outPortItemScrollWidget; }
};
#endif // OUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__
