#ifndef IMAGEOUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__
#define IMAGEOUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class ImageOutPortItemWidget;
class QVBoxLayout;
class OutputPort;
class ImageOutPortItemScrollWidget : public QWidget {
	Q_OBJECT;
protected:
	std::list< ImageOutPortItemWidget * > imageOutPortItemWidgetList;
	QVBoxLayout *mainLayout;
public:
	ImageOutPortItemScrollWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~ImageOutPortItemScrollWidget( ) override;
	virtual bool appendOutputItem( OutputPort *output_port_ptr, const QImage &image_ref_obj );
	virtual bool clear( );
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // IMAGEOUTPORTITEMSCROLLWIDGET_H_H_HEAD__FILE__
