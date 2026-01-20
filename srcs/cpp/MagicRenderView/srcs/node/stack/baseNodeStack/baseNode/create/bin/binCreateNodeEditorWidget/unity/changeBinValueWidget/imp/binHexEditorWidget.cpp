#include "binHexEditorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <widget/lineEdit/hexLineEdit.h>
void BinHexEditorWidget::valueChanged_Slot( const QString &text ) {
	bool resultOk;
	qlonglong longLong = text.toLongLong( &resultOk, 16 );
	if( resultOk == false )
		return;
	if( binOr == longLong )
		return;
	binOr = 0;
	binOr = binOr | longLong;
	emit value_change_signal( binOr );
}
BinHexEditorWidget::BinHexEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area ) : ChangeBinValueWidget( bin_create_unity_node_editor_scroll_area ) {
	
	hexEditor = new HexLineEdit( UINT8_MAX, this );
	maxLen = hexEditor->maxLength( );
	
	title = new QLabel( tr( "十六进制:" ), this );
	
	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( title );
	mainLayout->addWidget( hexEditor );

	connect( hexEditor, &QLineEdit::textChanged, this, &BinHexEditorWidget::valueChanged_Slot );
}
void BinHexEditorWidget::updateValue( uint8_t new_value ) {
	if( binOr == new_value )
		return;
	hexEditor->setText( tr( "%1" ).arg( new_value, maxLen, 16, '0' ) );
}
