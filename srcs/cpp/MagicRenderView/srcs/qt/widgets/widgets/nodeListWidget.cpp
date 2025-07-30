#include "./nodeListWidget.h"

#include <QPainter>
#include <QListWidget>
#include <qboxlayout.h>
#include <qfileinfo.h>

#include "gridWidget.h"

#include "../../application/application.h"

#include "../../stacks/funStack/IFunStack.h"
#include "../../stacks/varStack/IVarStack.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	mainLayout = new QHBoxLayout( this );
	mainLayout->setSpacing( 0 );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	nodeTypeList = new QListWidget( this );
	nodeGeneraterList = new GridWidget( this );
	mainLayout->addWidget( nodeTypeList, 2 );
	mainLayout->addWidget( nodeGeneraterList, 8 );

	applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto funStacks = applicationInstancePtr->getFunStacks( );

	for( auto &item : funStacks ) {
		IFunStack *element = item.get( );
		QString typeName = element->metaObject( )->className( );
		typeName.append( "/" ).append( element->getName( ) );
		qDebug( ) << typeName;
	}
}
NodeListWidget::~NodeListWidget( ) {
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::blue );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
