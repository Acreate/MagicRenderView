#include "floatCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <widget/validatorWidget/double/doubleValueValidatorWidget.h>

void FloatCreateUnityNodeEditorScrollArea::appendValidatorWidget( ValidatorWidget *append_ptr ) {
	mainLayout->addWidget( append_ptr );
	lineFinishedEditorVector.emplace_back( append_ptr );
	connect( append_ptr, &ValidatorWidget::currentEditing_Signal, this, &FloatCreateUnityNodeEditorScrollArea::overEditorFinish_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusIn_Signal, this, &FloatCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot );
	connect( append_ptr, &ValidatorWidget::currentEditingFocusOut_Signal, this, &FloatCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot );
}
void FloatCreateUnityNodeEditorScrollArea::overEditorFinish_Slot( ValidatorWidget *sender_ptr, const QString &dec_txt ) {
	bool isOk;
	double converValue = dec_txt.toDouble( &isOk );
	if( isOk == false )
		return; // 转换失败
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( sender_ptr != lineEditArray[ index ] && lineEditArray[ index ] != currentEditorValidator )
			lineEditArray[ index ]->setDecValue( dec_txt );
	emit editingFinished_Signal( converValue );
}
void FloatCreateUnityNodeEditorScrollArea::currentEditingFocusIn_Slot( ValidatorWidget *sender_ptr ) {
	currentEditorValidator = sender_ptr;
}
void FloatCreateUnityNodeEditorScrollArea::currentEditingFocusOut_Slot( ValidatorWidget *sender_ptr ) {
	if( sender_ptr == currentEditorValidator )
		currentEditorValidator = nullptr;
}
FloatCreateUnityNodeEditorScrollArea::FloatCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, double current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	auto number = QString::number( currentVar );

	doubleValueValidatorWidget = new DoubleValueValidatorWidget( tr( "浮点:" ), number, this );
	appendValidatorWidget( doubleValueValidatorWidget );
}
void FloatCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool FloatCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
FloatCreateUnityNodeEditorScrollArea::~FloatCreateUnityNodeEditorScrollArea( ) {

}
void FloatCreateUnityNodeEditorScrollArea::setCurrentVar( double current_var ) {
	currentVar = current_var;
	size_t count = lineFinishedEditorVector.size( );
	auto lineEditArray = lineFinishedEditorVector.data( );
	size_t index;
	QString decValue = QString::number( current_var );
	for( index = 0; index < count; ++index )
		lineEditArray[ index ]->setDecValue( decValue );
}
