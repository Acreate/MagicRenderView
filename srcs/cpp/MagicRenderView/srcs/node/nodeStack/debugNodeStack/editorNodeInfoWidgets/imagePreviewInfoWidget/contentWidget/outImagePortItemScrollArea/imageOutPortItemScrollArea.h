#ifndef IMAGEOUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__
#define IMAGEOUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class ImageOutPortItemScrollWidget;
class OutPortItemWidget;
class ImageOutPortItemScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	ImageOutPortItemScrollWidget *imageOutPortItemScrollWidget;
public:
	ImageOutPortItemScrollArea( QWidget *parent );
	virtual ImageOutPortItemScrollWidget * getImageOutPortItemScrollWidget( ) const { return imageOutPortItemScrollWidget; }
};
#endif // IMAGEOUTPORTITEMSCROLLAREA_H_H_HEAD__FILE__
