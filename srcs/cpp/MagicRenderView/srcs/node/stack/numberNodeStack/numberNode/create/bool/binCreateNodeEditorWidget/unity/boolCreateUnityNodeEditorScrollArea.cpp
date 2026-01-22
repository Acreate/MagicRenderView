#include "boolCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/bool/boolValueValidatorWidget.h>

void BoolCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &BoolCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &BoolCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &BoolCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void BoolCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
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
void BoolCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void BoolCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
BoolCreateUnityNodeEditorScrollArea::BoolCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, bool current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );
	appendValidatorWidget( new BoolValueValidatorWidget( tr( "布尔:" ), number, this ) );
}
void BoolCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool BoolCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BoolCreateUnityNodeEditorScrollArea::~BoolCreateUnityNodeEditorScrollArea( ) {

}
void BoolCreateUnityNodeEditorScrollArea::setCurrentVar( uint8_t current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
