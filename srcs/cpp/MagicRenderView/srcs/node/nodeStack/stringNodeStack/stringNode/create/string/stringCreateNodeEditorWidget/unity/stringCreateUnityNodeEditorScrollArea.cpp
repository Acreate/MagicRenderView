#include "stringCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/string/stringValueValidatorWidget.h>

void StringCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &StringCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &StringCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &StringCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void StringCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	emit editingFinished_Signal( dec_txt );
}
void StringCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void StringCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
StringCreateUnityNodeEditorScrollArea::StringCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QString &current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	stringValueValidatorWidget = new StringValueValidatorWidget( tr( "编辑内容:" ), current_var, this );
	mainLayout->addWidget( stringValueValidatorWidget );
	lineFinishedEditorVector.emplace_back( stringValueValidatorWidget );
	connect( stringValueValidatorWidget, &ValidatorWidget::overEditorFinish_Signal, this, &StringCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( stringValueValidatorWidget, &ValidatorWidget::currentEditingFocusIn_Signal, this, &StringCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( stringValueValidatorWidget, &ValidatorWidget::currentEditingFocusOut_Signal, this, &StringCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void StringCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool StringCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
StringCreateUnityNodeEditorScrollArea::~StringCreateUnityNodeEditorScrollArea( ) {

}
void StringCreateUnityNodeEditorScrollArea::setCurrentVar( QString current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( current_var );
}
