#include "intCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/int64/int64DecValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64BinValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64HexValidatorWidget.h>
#include <widget/validatorWidget/uint64/uInt64OctValidatorWidget.h>

void IntCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &IntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void IntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	size_t count;
	ValidatorWidget **lineEditArray;
	size_t index;
	Type64Bin type64BinVar;
	QString converToDec;

	type64BinVar.ulongLong = dec_txt.toULongLong( &isOk );
	if( isOk == true ) {
		count = lineFinishedEditorVector.size( );
		lineEditArray = lineFinishedEditorVector.data( );
		for( index = 0; index < count; ++index )
			if( sender_ptr != lineEditArray[ index ] )
				if( lineEditArray[ index ] != currentEditorValidator )
					lineEditArray[ index ]->setDecValue( dec_txt );
		if( currentEditorValidator != int64DecValidatorWidget && sender_ptr != int64DecValidatorWidget ) {
			converToDec = QString::number( type64BinVar.longLong );
			int64DecValidatorWidget->setDecValue( converToDec );
		}
		emit editingFinished_Signal( type64BinVar.longLong );
	}
}
void IntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void IntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
void IntCreateUnityNodeEditorScrollArea::intOverEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	size_t count;
	ValidatorWidget **lineEditArray;
	size_t index;
	Type64Bin type64BinVar;
	type64BinVar.longLong = dec_txt.toLongLong( &isOk );
	if( isOk == true ) {
		count = lineFinishedEditorVector.size( );
		lineEditArray = lineFinishedEditorVector.data( );
		for( index = 0; index < count; ++index )  // 处理无符号
			lineEditArray[ index ]->setDecValue( dec_txt );
		emit editingFinished_Signal( type64BinVar.longLong );
	}
}
IntCreateUnityNodeEditorScrollArea::IntCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, int64_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );

	// 特殊的节点

	int64DecValidatorWidget = new Int64DecValidatorWidget( tr( "十进制:" ), number, this );
	mainLayout->addWidget( int64DecValidatorWidget );
	lineFinishedEditorVector.emplace_back( int64DecValidatorWidget );
	connect( int64DecValidatorWidget, &ValidatorWidget::currentEditing_Signal, this, &IntCreateUnityNodeEditorScrollArea::intOverEditorFinish_Slot );
	connect( int64DecValidatorWidget, &ValidatorWidget::currentEditingFocusIn_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( int64DecValidatorWidget, &ValidatorWidget::currentEditingFocusOut_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );

	appendValidatorWidget( new UInt64HexValidatorWidget( tr( "十六进制:" ), number, this ) );
	appendValidatorWidget( new UInt64OctValidatorWidget( tr( "八进制:" ), number, this ) );
	appendValidatorWidget( new UInt64BinValidatorWidget( tr( "二进制:" ), number, this ) );
}
void IntCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool IntCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
IntCreateUnityNodeEditorScrollArea::~IntCreateUnityNodeEditorScrollArea( ) {

}
void IntCreateUnityNodeEditorScrollArea::setCurrentVar( int64_t current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
