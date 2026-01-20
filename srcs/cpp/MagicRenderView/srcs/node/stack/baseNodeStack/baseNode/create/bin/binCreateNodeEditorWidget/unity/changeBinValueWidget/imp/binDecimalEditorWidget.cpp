#include "binDecimalEditorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <widget/lineEdit/decLineEdit.h>
void BinDecimalEditorWidget::valueChanged_Slot( const QString &text ) {
	bool resultOk;
	qlonglong longLong = text.toLongLong( &resultOk, 10 );
	if( resultOk == false )
		return;
	if( binOr == longLong )
		return;
	binOr = 0;
	binOr = binOr | longLong;
	emit value_change_signal( binOr );
}
BinDecimalEditorWidget::BinDecimalEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area ) : ChangeBinValueWidget( bin_create_unity_node_editor_scroll_area ) {
	decEditor = new DecLineEdit( UINT8_MAX, this );
	maxLen = decEditor->maxLength( );

	title = new QLabel( tr( "十进制:" ), this );

	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( title );
	mainLayout->addWidget( decEditor );

	connect( decEditor, &QLineEdit::textChanged, this, &BinDecimalEditorWidget::valueChanged_Slot );
}
void BinDecimalEditorWidget::updateValue( uint8_t new_value ) {
	if( binOr == new_value )
		return;
	decEditor->setText( tr( "%1" ).arg( new_value, maxLen, 10, '0' ) );
}
