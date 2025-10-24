#include <QLabel>
#include <QPainter>
#include <qboxlayout.h>

#include "GenerateListItemWidget.h"

#include "../../varType/I_Var.h"
GenerateListItemWidget::GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), var( var ) {
	auto mainLayout = new QHBoxLayout( this );
	QLabel *titile = new QLabel( this );
	titile->setText( var.get( )->getVarName( ) );
	mainLayout->addWidget( titile );
}
GenerateListItemWidget::~GenerateListItemWidget( ) {
	emit releaseThisPtr( this );
}
void GenerateListItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	//painter.fillRect( contentsRect( ), Qt::GlobalColor::blue );
	int penWidth = 5;
	int doublePenWidth = penWidth * 2;
	auto pen = painter.pen( );
	pen.setWidth( penWidth );
	pen.setColor( Qt::GlobalColor::darkBlue );
	painter.drawRect( penWidth, penWidth, width( ) - doublePenWidth, height( ) - doublePenWidth );
}
