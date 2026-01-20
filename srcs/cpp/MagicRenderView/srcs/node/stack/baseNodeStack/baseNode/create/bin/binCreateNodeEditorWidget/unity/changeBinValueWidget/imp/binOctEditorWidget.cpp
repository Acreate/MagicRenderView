#include "binOctEditorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpressionValidator>

#include "validator/decValidator.h"
void BinOctEditorWidget::valueChanged_Slot( const QString &text ) {

	bool resultOk;
	qlonglong longLong = text.toLongLong( &resultOk, 8 );
	if( resultOk == false )
		return;
	if( binOr == longLong )
		return;
	binOr = 0;
	binOr = binOr | longLong;
	emit value_change_signal( binOr );
}
BinOctEditorWidget::BinOctEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area ) : ChangeBinValueWidget( bin_create_unity_node_editor_scroll_area ) {
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 8 ).length( );
	octEditor = new QLineEdit( this );
	octEditor->setValidator( new DecValidator( octEditor ) );
	title = new QLabel( tr( "八进制:" ), this );
	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( title );
	mainLayout->addWidget( octEditor );
	octEditor->setMaxLength( maxLen );
	connect( octEditor, &QLineEdit::textChanged, this, &BinOctEditorWidget::valueChanged_Slot );
}
void BinOctEditorWidget::updateValue( uint8_t new_value ) {
	if( binOr == new_value )
		return;
	octEditor->setText( tr( "%1" ).arg( new_value, maxLen, 8, '0' ) );
}
