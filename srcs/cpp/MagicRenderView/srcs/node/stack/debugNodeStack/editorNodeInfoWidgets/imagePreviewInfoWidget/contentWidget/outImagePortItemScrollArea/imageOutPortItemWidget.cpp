#include "imageOutPortItemWidget.h"

#include <node/node/node.h>
#include <node/port/outputPort/outputPort.h>
#include <QLabel>
#include <QPainter>
#include <QTextEdit>
#include <QVBoxLayout>
ImageOutPortItemWidget::ImageOutPortItemWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {

	outputPortPtrName = new QLabel( this );
	outputPreviewImage = new QLabel( this );

	auto defaultLayout = layout( );
	if( defaultLayout )
		delete defaultLayout;

	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( outputPortPtrName );
	mainLayout->addWidget( outputPreviewImage );
}
void ImageOutPortItemWidget::setInfo( OutputPort *output_port_ptr, const QImage &image_ref_obj ) {
	outputPortPtrName->setText( output_port_ptr->getParentNode( )->toQString( ) + "/" + output_port_ptr->getPortName( ) );
	outputPreviewImage->setPixmap( QPixmap::fromImage( image_ref_obj ) );
}
void ImageOutPortItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
