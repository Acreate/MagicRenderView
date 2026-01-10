
#include "floatGenerateTool.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <qpushbutton.h>
FloatGenerateTool::FloatGenerateTool( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	auto mainLayout = new QHBoxLayout( this );
	insertIndexComboBox = new QComboBox( this );
	insertBtn = new QPushButton( tr( "插入" ), this );
	mainLayout->addWidget( insertIndexComboBox, 0, Qt::AlignLeft );
	mainLayout->addWidget( insertBtn, 0, Qt::AlignRight );
	insertIndexComboBox->setEditable( false );
	connect( insertBtn, &QPushButton::clicked, [this]( ) {
		emit addItem_signal( this, insertIndexComboBox->currentIndex( ), insertIndexComboBox->currentText( ), insertIndexComboBox->currentData( ) );
	} );
}
void FloatGenerateTool::setMaxIndex( const size_t &index ) {

	int currentCount = insertIndexComboBox->count( );
	size_t foreachIndex;
	if( currentCount != index )
		if( currentCount > index ) {
			currentCount = currentCount - index;
			for( foreachIndex = 0; foreachIndex < currentCount; ++foreachIndex )
				insertIndexComboBox->removeItem( 0 );
		} else {
			currentCount = index - currentCount;
			for( foreachIndex = 0; foreachIndex < currentCount; ++foreachIndex )
				insertIndexComboBox->addItem( tr( "" ) );
		}

	for( foreachIndex = 0; foreachIndex < index; ++foreachIndex )
		insertIndexComboBox->setItemText( foreachIndex, QString::number( foreachIndex ) );
}
