#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <qboxlayout.h>

#include "GenerateListItemWidget.h"
#include "varEditorWidget.h"

#include "../../varType/I_Var.h"
GenerateListItemWidget::GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), var( var ) {
	varEditorWidget = new VarEditorWidget( var );
	auto mainLayout = new QHBoxLayout( this );
	QLabel *titile = new QLabel( this );
	titile->setText( var.get( )->getVarName( ) );
	mainLayout->addWidget( titile );
	QPushButton *delBtn = new QPushButton( tr( "删除" ), this );
	mainLayout->addWidget( delBtn, 0, Qt::AlignRight );
	connect( delBtn, &QPushButton::clicked, [this]( ) {
		delete this;
	} );
}
GenerateListItemWidget::~GenerateListItemWidget( ) {
	emit releaseThisPtr( this );
	delete varEditorWidget;
}
bool GenerateListItemWidget::showVarEditorWidget( ) const {
	if( varEditorWidget == nullptr || var == nullptr || var->getVarPtr( ) == nullptr )
		return false;
	varEditorWidget->show( );
	varEditorWidget->raise( );
	return true;
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
void GenerateListItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	showVarEditorWidget( );
}
