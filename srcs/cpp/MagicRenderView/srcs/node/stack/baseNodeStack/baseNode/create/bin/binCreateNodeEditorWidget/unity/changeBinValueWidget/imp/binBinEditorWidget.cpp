#include "binBinEditorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <widget/lineEdit/binLineEdit.h>
void BinBinEditorWidget::valueChanged_Slot( const QString &text ) {

	bool resultOk;
	qlonglong longLong = text.toLongLong( &resultOk, 2 );
	if( resultOk == false )
		return;
	if( binOr == longLong )
		return;
	binOr = 0;
	binOr = binOr | longLong;
	emit value_change_signal( binOr );
}
BinBinEditorWidget::BinBinEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area ) : ChangeBinValueWidget( bin_create_unity_node_editor_scroll_area ) {
	
	binEditor = new BinLineEdit( UINT8_MAX, this );
	maxLen = binEditor->maxLength( );
	
	title = new QLabel( tr( "二进制:" ), this );
	
	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( title );
	mainLayout->addWidget( binEditor );
	
	connect( binEditor, &QLineEdit::textChanged, this, &BinBinEditorWidget::valueChanged_Slot );
}
void BinBinEditorWidget::updateValue( uint8_t new_value ) {
	if( binOr == new_value )
		return;
	binEditor->setText( tr( "%1" ).arg( new_value, maxLen, 2, '0' ) );
}
