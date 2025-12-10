#include "generateItemWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <qpushbutton.h>

void GenerateItemWidget::updateInfoString( ) {
	auto title = infoFormmattion.arg( index ).arg( varValue );
	showInfo->setText( title );
}
GenerateItemWidget::GenerateItemWidget( QWidget *parent, const Qt::WindowFlags &f ) {
	auto mainLayout = new QHBoxLayout( this );
	showInfo = new QLabel( this );
	removeButton = new QPushButton( tr( "删除" ), this );
	mainLayout->addWidget( showInfo, 0, Qt::AlignmentFlag::AlignLeading );
	mainLayout->addWidget( removeButton, 0, Qt::AlignmentFlag::AlignRight );
	infoFormmattion = QString( tr( "int [ %1 ] = %2" ) );
	connect( removeButton, &QPushButton::clicked, [this]( ) {
		emit clickRemoveItemBtn( this, index, varValue );
	} );
}
void GenerateItemWidget::setInfo( const size_t &index, const QString &var_value ) {
	this->index = QString::number( index );
	this->varValue = var_value;
	updateInfoString( );
}
