#include "generateInfoEditorTitle.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <qpushbutton.h>
GenerateInfoEditorTitle::GenerateInfoEditorTitle( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	varTypeName = new QLabel( tr( "变量类型" ), this );
	varName = new QLineEdit( this );
	addendVarListBtn = new QPushButton( tr( "添加" ), this );
	connect( addendVarListBtn, &QPushButton::clicked, [this]( ) {
		emit createVar( varTypeName->text( ), varName->text( ) );
	} );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( varTypeName );
	mainLayout->addSpacing( 5 );
	mainLayout->addWidget( varName );
	mainLayout->addSpacing( 5 );
	mainLayout->addWidget( addendVarListBtn );
	mainLayout->setContentsMargins( 5, 5, 5, 5 );
}
void GenerateInfoEditorTitle::clearVarName( ) {
	varName->clear( );
}
void GenerateInfoEditorTitle::setVarTypeName( const QString &new_var_type_name ) {
	varTypeName->setText( new_var_type_name );
}
