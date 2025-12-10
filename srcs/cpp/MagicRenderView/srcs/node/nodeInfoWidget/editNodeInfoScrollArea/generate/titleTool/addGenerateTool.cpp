#include "addGenerateTool.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <qpushbutton.h>
AddGenerateTool::AddGenerateTool( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	auto mainLayout = new QHBoxLayout( this );
	insertIndexComboBox = new QComboBox( this );
	varEditor = new QLineEdit( this );
	insertBtn = new QPushButton( tr( "插入" ), this );
	mainLayout->addWidget( insertIndexComboBox, 0, Qt::AlignLeft );
	mainLayout->addWidget( varEditor, 0, Qt::AlignRight );
	mainLayout->addWidget( insertBtn, 0, Qt::AlignRight );
	insertIndexComboBox->setEditable( false );
	connect( insertBtn, &QPushButton::clicked, [this]( ) {
		int currentIndex = insertIndexComboBox->currentIndex( );
		emit addItem( this, currentIndex, varEditor->text( ) );
	} );
}
void AddGenerateTool::setMaxIndex( const size_t &index ) {
	insertIndexComboBox->setMaxCount( index );
	for( size_t foreachIndex = 0; foreachIndex < index; ++foreachIndex )
		insertIndexComboBox->setItemText( foreachIndex, QString::number( index ) );
}
