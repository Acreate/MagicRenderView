#include "binHexEditorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpressionValidator>

#include "validator/hexValidator.h"
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
	hexEditor = new QLineEdit( this );
	hexEditor->setValidator( new HexValidator( hexEditor ) );
	title = new QLabel( tr( "十六进制:" ), this );
	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( title );
	mainLayout->addWidget( hexEditor );

	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 16 ).length( );
	hexEditor->setMaxLength( maxLen );
	connect( hexEditor, &QLineEdit::textChanged, this, &BinHexEditorWidget::valueChanged_Slot );
}
void BinHexEditorWidget::updateValue( uint8_t new_value ) {
	if( binOr == new_value )
		return;
	hexEditor->setText( tr( "%1" ).arg( new_value, maxLen, 16, '0' ) );
}
