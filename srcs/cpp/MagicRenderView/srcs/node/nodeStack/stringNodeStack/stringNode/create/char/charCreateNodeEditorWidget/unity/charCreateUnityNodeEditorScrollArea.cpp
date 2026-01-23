#include "charCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/char/charValueValidatorWidget.h>
#include <widget/validatorWidget/int64/int64DecValidatorWidget.h>
#include <widget/validatorWidget/uint16/uInt16BinValidatorWidget.h>
#include <widget/validatorWidget/uint16/uInt16HexValidatorWidget.h>
#include <widget/validatorWidget/uint16/uInt16OctValidatorWidget.h>

void CharCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &CharCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &CharCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &CharCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void CharCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	QString buff;
	auto longLong = dec_txt[ 0 ].unicode( );
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		if( sender_ptr != lineEditArray[ index ] )
			if( lineEditArray[ index ] != currentEditorValidator )
				lineEditArray[ index ]->setDecValue( dec_txt );

	if( sender_ptr != currentEditorValidator && currentEditorValidator != charValueValidatorWidget ) {
		charValueValidatorWidget->setDecValue( dec_txt );
		if( charValueValidatorWidget->getDecValue( buff ) )
			emit editingFinished_Signal( buff.data( )[ 0 ] );
	}

}
void CharCreateUnityNodeEditorScrollArea::overCharEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	if( sender_ptr != charValueValidatorWidget )
		return;
	if( dec_txt.isEmpty( ) )
		return;
	QChar firstChar = dec_txt[ 0 ];
	auto longLong = firstChar.unicode( );
	QString setVar = QString::number( longLong );
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		if( sender_ptr != lineEditArray[ index ] )
			if( lineEditArray[ index ] != currentEditorValidator )
				lineEditArray[ index ]->setDecValue( setVar );
	emit editingFinished_Signal( firstChar );
}
void CharCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void CharCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
CharCreateUnityNodeEditorScrollArea::CharCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QChar &current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar.unicode( ) );
	charValueValidatorWidget = new CharValueValidatorWidget( tr( "字符:" ), current_var, this );

	mainLayout->addWidget( charValueValidatorWidget );
	lineFinishedEditorVector.emplace_back( charValueValidatorWidget );
	connect( charValueValidatorWidget, &ValidatorWidget::currentEditing_Signal, this, &CharCreateUnityNodeEditorScrollArea::overCharEditorFinish_Slot );
	connect( charValueValidatorWidget, &ValidatorWidget::currentEditingFocusIn_Signal, this, &CharCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( charValueValidatorWidget, &ValidatorWidget::currentEditingFocusOut_Signal, this, &CharCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );

	appendValidatorWidget( new Int64DecValidatorWidget( tr( "十进制:" ), number, this ) );
	appendValidatorWidget( new UInt16HexValidatorWidget( tr( "十六进制:" ), number, this ) );
	appendValidatorWidget( new UInt16OctValidatorWidget( tr( "八进制:" ), number, this ) );
	appendValidatorWidget( new UInt16BinValidatorWidget( tr( "二进制:" ), number, this ) );
}
void CharCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool CharCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
CharCreateUnityNodeEditorScrollArea::~CharCreateUnityNodeEditorScrollArea( ) {

}
void CharCreateUnityNodeEditorScrollArea::setCurrentVar( QChar current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var.unicode( ) );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
