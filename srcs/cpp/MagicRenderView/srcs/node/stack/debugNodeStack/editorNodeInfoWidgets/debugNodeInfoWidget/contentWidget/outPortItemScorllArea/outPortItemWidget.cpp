#include "outPortItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <QTextEdit>
#include <QVBoxLayout>

#include "../../../../../../node/node.h"
#include "../../../../../../port/outputPort/outputPort.h"
OutPortItemWidget::OutPortItemWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	auto defaultLayout = layout( );
	if( defaultLayout )
		delete defaultLayout;
	mainLayout = new QVBoxLayout( this );
	outputPortPtrName = new QLabel( this );
	outputPortMsg = new QTextEdit( this );
	outputPortMsg->setLineWrapMode( QTextEdit::WidgetWidth );
	outputPortMsg->setWordWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );
	outputPortMsg->setReadOnly( true );
	mainLayout->addWidget( outputPortPtrName );
	mainLayout->addWidget( outputPortMsg );
}
void OutPortItemWidget::setInfo( OutputPort *output_port_ptr, const QString &msg ) {
	outputPortPtrName->setText( output_port_ptr->getParentNode( )->toQString( ) + "/" + output_port_ptr->getPortName( ) );
	outputPortMsg->setText( msg );
}
void OutPortItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	//QPainter painter( this );
	//auto pen = painter.pen( );
	//pen.setWidth( 2 );
	//int widgetWidth = width( );
	//painter.drawRect( 2, 2, widgetWidth - 4, height( ) - 4 );
}
