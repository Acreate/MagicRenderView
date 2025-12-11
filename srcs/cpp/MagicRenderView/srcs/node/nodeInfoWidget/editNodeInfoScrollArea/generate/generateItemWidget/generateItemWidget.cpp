#include "generateItemWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <qpushbutton.h>

void GenerateItemWidget::updateInfoString( ) {
	auto title = infoFormmattion.arg( QString::number( index ) );
	showIndexInfo->setText( title );
	editorVarInfo->setText( varValue );
}
GenerateItemWidget::GenerateItemWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {

	mainLayout = new QHBoxLayout( this );
	showIndexInfo = new QLabel( this );
	editorVarInfo = new QLineEdit( this );
	removeButton = new QPushButton( tr( "删除" ), this );
	changeButton = new QPushButton( tr( "应用" ), this );
	restoryButton = new QPushButton( tr( "还原" ), this );
	mainLayout->addWidget( showIndexInfo, 2 );
	mainLayout->addWidget( editorVarInfo, 92 );
	mainLayout->addWidget( removeButton, 2 );
	mainLayout->addWidget( changeButton, 2 );
	mainLayout->addWidget( restoryButton, 2 );
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
void GenerateItemWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
