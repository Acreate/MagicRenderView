#include "binCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/uint8/uInt8BinValidatorWidget.h>
#include <widget/validatorWidget/uint8/uInt8DecValidatorWidget.h>
#include <widget/validatorWidget/uint8/uInt8HexValidatorWidget.h>
#include <widget/validatorWidget/uint8/uInt8OctValidatorWidget.h>

void BinCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &BinCreateUnityNodeEditorScrollArea::currentEditing_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &BinCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &BinCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void BinCreateUnityNodeEditorScrollArea::currentEditing_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	qlonglong longLong = dec_txt.toULongLong( &isOk );
	if( isOk == false )
		return; // 转换失败
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		if( sender_ptr != lineEditArray[ index ] && lineEditArray[ index ] != currentEditorValidator )
			lineEditArray[ index ]->setDecValue( dec_txt );
	emit editingFinished_Signal( longLong );
}
void BinCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void BinCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
BinCreateUnityNodeEditorScrollArea::BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );
	appendValidatorWidget( new UInt8DecValidatorWidget( tr( "十进制:" ), number, this ) );
	appendValidatorWidget( new UInt8HexValidatorWidget( tr( "十六进制:" ), number, this ) );
	appendValidatorWidget( new UInt8OctValidatorWidget( tr( "八进制:" ), number, this ) );
	appendValidatorWidget( new UInt8BinValidatorWidget( tr( "二进制:" ), number, this ) );
}
void BinCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool BinCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BinCreateUnityNodeEditorScrollArea::~BinCreateUnityNodeEditorScrollArea( ) {

}
void BinCreateUnityNodeEditorScrollArea::setCurrentVar( uint8_t current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
