#ifndef OUTPORTITEMSCORLLAREA_H_H_HEAD__FILE__
#define OUTPORTITEMSCORLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class OutPortItemScorllWidget;
class OutPortItemWidget;
class OutPortItemScorllArea : public QScrollArea {
	Q_OBJECT;
protected:
	OutPortItemScorllWidget* outPortItemScorllWidget;
public:
	OutPortItemScorllArea( QWidget *parent );
	virtual OutPortItemScorllWidget * getOutPortItemScorllWidget( ) const { return outPortItemScorllWidget; }
};

#endif // OUTPORTITEMSCORLLAREA_H_H_HEAD__FILE__
