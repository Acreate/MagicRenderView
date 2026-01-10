#include "uIntGenerateItemWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <qpushbutton.h>

UIntGenerateItemWidget::UIntGenerateItemWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	mainLayout = new QHBoxLayout( this );
	showIndexInfo = new QLabel( this );
	dragLabel = new QLabel( this );
	editorVarInfo = new QLineEdit( this );
	mainLayout->addWidget( dragLabel, 2 );
	mainLayout->addWidget( showIndexInfo, 2 );
	mainLayout->addWidget( editorVarInfo, 92 );
	infoFormmattion = QString( tr( "uint [ %1 ]" ) );
	QImage image( ":/nodeitemIco/option.png" );
	dragLabel->setPixmap( QPixmap::fromImage( image ) );
	popMenu = new QMenu( this );
	auto changeAction = popMenu->addAction( tr( "更改" ) );
	auto removeAction = popMenu->addAction( tr( "删除" ) );
	auto restoryAction = popMenu->addAction( tr( "还原" ) );
	connect( changeAction, &QAction::triggered, [this]( ) {
		emit changeVar( this );
	} );
	connect( removeAction, &QAction::triggered, [this]( ) {
		emit removeVar( this );
	} );
	connect( restoryAction, &QAction::triggered, [this]( ) {
		emit restoryVar( this );
	} );
	setInfo( 0, 0 );
}
void UIntGenerateItemWidget::setInfo( const size_t &index, const QString &var_value ) {
	auto title = infoFormmattion.arg( QString::number( index ) );
	showIndexInfo->setText( title );
	editorVarInfo->setText( var_value );
}
void UIntGenerateItemWidget::setIndex( const size_t &index ) {
	auto title = infoFormmattion.arg( QString::number( index ) );
	showIndexInfo->setText( title );
}
bool UIntGenerateItemWidget::isDragWidgetPos( const QPoint &pos ) {
	if( geometry( ).contains( pos ) )
		return true;
	return false;
}
QString UIntGenerateItemWidget::getVarValue( ) const { return editorVarInfo->text( ); }
