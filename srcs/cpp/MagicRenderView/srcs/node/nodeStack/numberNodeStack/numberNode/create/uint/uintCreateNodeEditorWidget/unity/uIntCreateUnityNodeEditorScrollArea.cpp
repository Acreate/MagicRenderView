#include "uIntCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/uint64/uInt64BinValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64DecValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64HexValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64OctValidatorWidget.h>

void UIntCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &UIntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &UIntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &UIntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void UIntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	size_t count;
	ValidatorWidget **lineEditArray;
	size_t index;
	qlonglong longLong;
	qulonglong ulongLong;

	ulongLong = dec_txt.toULongLong( &isOk );
	if( isOk == true ) {
		count = lineFinishedEditorVector.size( );
		lineEditArray = lineFinishedEditorVector.data( );
		for( index = 0; index < count; ++index )
			if( sender_ptr != lineEditArray[ index ] )
				if( lineEditArray[ index ] != currentEditorValidator )
					lineEditArray[ index ]->setDecValue( dec_txt );
		emit editingFinished_Signal( ulongLong );
	}

	longLong = dec_txt.toLongLong( &isOk );
	if( isOk == true ) {
		count = lineFinishedEditorVector.size( );
		lineEditArray = lineFinishedEditorVector.data( );
		for( index = 0; index < count; ++index )
			if( sender_ptr != lineEditArray[ index ] )
				if( lineEditArray[ index ] != currentEditorValidator )
					lineEditArray[ index ]->setDecValue( dec_txt );
		emit editingFinished_Signal( longLong );
	}
}
void UIntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void UIntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
UIntCreateUnityNodeEditorScrollArea::UIntCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint64_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );
	appendValidatorWidget( new UInt64DecValidatorWidget( tr( "十进制:" ), number, this ) );
	appendValidatorWidget( new UInt64HexValidatorWidget( tr( "十六进制:" ), number, this ) );
	appendValidatorWidget( new UInt64OctValidatorWidget( tr( "八进制:" ), number, this ) );
	appendValidatorWidget( new UInt64BinValidatorWidget( tr( "二进制:" ), number, this ) );
}
void UIntCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool UIntCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
UIntCreateUnityNodeEditorScrollArea::~UIntCreateUnityNodeEditorScrollArea( ) {

}
void UIntCreateUnityNodeEditorScrollArea::setCurrentVar( uint64_t current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
