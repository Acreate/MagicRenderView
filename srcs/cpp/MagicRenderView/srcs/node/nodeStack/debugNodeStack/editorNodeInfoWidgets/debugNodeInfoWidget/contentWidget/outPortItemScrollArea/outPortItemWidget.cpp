#include "outPortItemWidget.h"

#include <node/node/node.h>
#include <node/port/outputPort/outputPort.h>
#include <QLabel>
#include <QPainter>
#include <QTextEdit>
#include <QVBoxLayout>
OutPortItemWidget::OutPortItemWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {

	outputPortPtrName = new QLabel( this );
	outputPortMsg = new QTextEdit( this );
	outputPortMsg->setLineWrapMode( QTextEdit::WidgetWidth );
	outputPortMsg->setWordWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );
	outputPortMsg->setReadOnly( true );
	outputPortMsg->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	outputPortMsg->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	

	auto defaultLayout = layout( );
	if( defaultLayout )
		delete defaultLayout;

	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( outputPortPtrName );
	mainLayout->addWidget( outputPortMsg );
}
void OutPortItemWidget::setInfo( OutputPort *output_port_ptr, const QString &msg ) {
	outputPortPtrName->setText( output_port_ptr->getParentNode( )->toQString( ) + "/" + output_port_ptr->getPortName( ) );
	outputPortMsg->setText( msg );
}
void OutPortItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
