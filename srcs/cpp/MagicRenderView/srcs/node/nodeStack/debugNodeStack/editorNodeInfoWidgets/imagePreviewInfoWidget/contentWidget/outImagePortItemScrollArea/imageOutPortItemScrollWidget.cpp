#include "imageOutPortItemScrollWidget.h"

#include <QPainter>
#include <QVBoxLayout>
#include "imageOutPortItemWidget.h"
ImageOutPortItemScrollWidget::ImageOutPortItemScrollWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
}
ImageOutPortItemScrollWidget::~ImageOutPortItemScrollWidget( ) {
	clear( );
}
bool ImageOutPortItemScrollWidget::appendOutputItem( OutputPort *output_port_ptr, const QImage &image_ref_obj ) {
	auto item = new ImageOutPortItemWidget( this );
	item->setInfo( output_port_ptr, image_ref_obj );
	mainLayout->addWidget( item );
	imageOutPortItemWidgetList.emplace_back( item );
	return true;
}
bool ImageOutPortItemScrollWidget::clear( ) {
	for( auto *item : imageOutPortItemWidgetList )
		delete item;
	imageOutPortItemWidgetList.clear( );
	return true;
}
void ImageOutPortItemScrollWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
