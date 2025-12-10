#include "generateItemWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <qpushbutton.h>

void GenerateItemWidget::updateInfoString( ) {
	auto title = infoFormmattion.arg( QString::number( index ) ).arg( varValue );
	showIndexInfo->setText( title );
}
GenerateItemWidget::GenerateItemWidget( QWidget *parent, const Qt::WindowFlags &f ) {
	auto mainLayout = new QHBoxLayout( this );
	showIndexInfo = new QLabel( this );
	editorVarInfo = new QLineEdit( this );
	editorVarInfo->setAlignment( Qt::AlignCenter );
	removeButton = new QPushButton( tr( "删除" ), this );
	changeButton = new QPushButton( tr( "应用" ), this );
	restoryButton = new QPushButton( tr( "还原" ), this );
	mainLayout->addWidget( showIndexInfo, 0, Qt::AlignmentFlag::AlignLeading );
	mainLayout->addWidget( editorVarInfo, 0, Qt::AlignmentFlag::AlignLeading );
	mainLayout->addWidget( removeButton, 0, Qt::AlignmentFlag::AlignRight );
	mainLayout->addWidget( changeButton, 0, Qt::AlignmentFlag::AlignRight );
	mainLayout->addWidget( restoryButton, 0, Qt::AlignmentFlag::AlignRight );
	infoFormmattion = QString( tr( "int [ %1 ]" ) );
	connect( removeButton, &QPushButton::clicked, [this]( ) {
		emit clickRemoveItemBtn( this, index, varValue );
	} );
	connect( changeButton, &QPushButton::clicked, [this]( ) {
		emit changeVar( this, index, varValue, editorVarInfo->text( ) );
	} );
	connect( restoryButton, &QPushButton::clicked, [this]( ) {
		emit restoryVar( this, index, varValue, editorVarInfo->text( ) );
	} );
}
void GenerateItemWidget::setInfo( const size_t &index, const QString &var_value ) {
	this->index = index;
	this->varValue = var_value;
	updateInfoString( );
}
