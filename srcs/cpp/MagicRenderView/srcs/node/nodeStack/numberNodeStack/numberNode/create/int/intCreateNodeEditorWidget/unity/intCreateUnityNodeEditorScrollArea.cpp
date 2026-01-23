#include "intCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/uint8/uint8BinValidatorWidget.h>
#include <widget/validatorWidget/uint8/uint8DecValidatorWidget.h>
#include <widget/validatorWidget/uint8/uint8HexValidatorWidget.h>
#include <widget/validatorWidget/uint8/uint8OctValidatorWidget.h>

void IntCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &IntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &IntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void IntCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	qlonglong longLong = dec_txt.toULongLong( &isOk );
	if( isOk == false )
		return; // 转换失败
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		if( sender_ptr != lineEditArray[ index ] )
			if( lineEditArray[ index ] != currentEditorValidator )
				lineEditArray[ index ]->setDecValue( dec_txt );
	emit editingFinished_Signal( longLong );
}
void IntCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void IntCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
IntCreateUnityNodeEditorScrollArea::IntCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );
	appendValidatorWidget( new Uint8DecValidatorWidget( tr( "十进制:" ), number, this ) );
	appendValidatorWidget( new Uint8HexValidatorWidget( tr( "十六进制:" ), number, this ) );
	appendValidatorWidget( new Uint8OctValidatorWidget( tr( "八进制:" ), number, this ) );
	appendValidatorWidget( new Uint8BinValidatorWidget( tr( "二进制:" ), number, this ) );
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
void IntCreateUnityNodeEditorScrollArea::setCurrentVar( uint8_t current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
