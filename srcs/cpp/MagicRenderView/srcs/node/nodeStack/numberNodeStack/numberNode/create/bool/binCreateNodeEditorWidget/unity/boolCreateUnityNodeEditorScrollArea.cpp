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
	if( boolValueValidatorWidget->getBoolValue( currentVar ) == false )
		return;
	emit editingFinished_Signal( currentVar ? 1 : 0 );
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

	boolValueValidatorWidget = new BoolValueValidatorWidget( tr( "布尔:" ), false, this );
	appendValidatorWidget( boolValueValidatorWidget );
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
void BoolCreateUnityNodeEditorScrollArea::setCurrentVar( bool current_var ) {
	boolValueValidatorWidget->setBoolValue( current_var );
}
