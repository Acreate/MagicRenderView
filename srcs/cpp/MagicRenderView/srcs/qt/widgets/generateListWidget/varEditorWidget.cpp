#include "varEditorWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <qboxlayout.h>

void VarEditorWidget::updateLayout( ) {

	auto rect = contentsRect( );
	int width = rect.width( );
	int height = rect.height( );
	int titileMid = ( width - titile->width( ) ) / 2;
	int y = 0;
	titile->move( titileMid, y );
	y += titile->height( );

	int varNameTitileWidth = varNameTitile->width( );
	int varVarTitileWidth = varVarTitile->width( );
	int buffWidth = varNameTitileWidth > varVarTitileWidth ? varNameTitileWidth : varVarTitileWidth;
	varNameTitile->move( 0, y );
	varNameLineEdit->move( buffWidth, y );
	y += varNameLineEdit->height( );

	varVarTitile->move( 0, y );
	varVarLineEdit->move( buffWidth, y );
	y += varVarLineEdit->height( );

	titileMid = ( width - applyVarChange->width( ) ) / 2;
	applyVarChange->move( titileMid, y );
	y += applyVarChange->height( );
	int varNameLineEditWidth = varNameLineEdit->width( );
	int varVarLineEditWidth = varVarLineEdit->width( );
	int varNameWidth = varNameTitileWidth + varNameLineEditWidth;
	int varVarWidth = varVarTitileWidth + varVarLineEditWidth;
	buffWidth = varNameWidth > varVarWidth ? varNameWidth : varVarWidth;
	if( y != height && width != buffWidth )
		setFixedSize( buffWidth, y );
	else if( y != height )
		setFixedHeight( y );
	else if( buffWidth != width )
		setFixedWidth( buffWidth );
}
void VarEditorWidget::initVarEditorInfo( ) {

}
VarEditorWidget::VarEditorWidget( const std_shared_ptr< I_Var > &editor_var ) : editorVar( editor_var ) {
	setFixedSize( 200, 250 );
	titile = new QLabel( tr( "变量编辑" ), this );

	varNameTitile = new QLabel( tr( "变量名称:" ), this );
	varNameLineEdit = new QLineEdit( this );

	varVarTitile = new QLabel( tr( "变量值:" ), this );
	varVarLineEdit = new QLineEdit( this );
	applyVarChange = new QPushButton( tr( "确定" ), this );
	initVarEditorInfo( );
}
void VarEditorWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
void VarEditorWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	updateLayout( );
	initVarEditorInfo( );
}
