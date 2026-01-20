#include "binCreateUnityNodeEditorScrollArea.h"

#include <QVBoxLayout>
#include <widget/intTypeLineEdit/titleLineEdit/binTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/decTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/hexTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/numberVarTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/octTitleLineEdit.h>

#include <widget/intTypeLineEdit/lineEdit/numberVarLineEdit.h>
#include "changeBinValueWidget/imp/binScrollBarEditorWidget.h"

void BinCreateUnityNodeEditorScrollArea::textChanged_Slot( NumberVarTitleLineEdit *sender_obj, NumberVarLineEdit *edite_event, const QString &text ) {
	uint64_t newValue;
	if( sender_obj->toUInt64( text, newValue ) == false )
		return;
	currentCom = sender_obj;
	size_t count;
	size_t index;
	count = compomentWidgetVector.size( );
	NumberVarTitleLineEdit **compomentArray;
	if( count ) {
		compomentArray = compomentWidgetVector.data( );
		for( index = 0; index < count; ++index )
			if( sender_obj != compomentArray[ index ] )
				compomentArray[ index ]->setVarToLineEdit( newValue );

	}

	ChangeBinValueWidget **changeBinValueWidgetArray;
	count = changeBinValueVector.size( );
	if( count && currentChange == nullptr ) {
		changeBinValueWidgetArray = changeBinValueVector.data( );
		for( index = 0; index < count; ++index )
			changeBinValueWidgetArray[ index ]->updateValue( newValue );

	}
	currentChange = nullptr;
	emit value_change_signal( 0 );
}
void BinCreateUnityNodeEditorScrollArea::valueChange_Slot( ChangeBinValueWidget *send_ptr, uint8_t new_value ) {
	currentChange = send_ptr;
	size_t count = changeBinValueVector.size( );
	size_t index;
	ChangeBinValueWidget **changeBinValueWidgetArray;
	if( count ) {
		changeBinValueWidgetArray = changeBinValueVector.data( );
		for( index = 0; index < count; ++index )
			if( changeBinValueWidgetArray[ index ] != send_ptr )
				changeBinValueWidgetArray[ index ]->updateValue( new_value );

	}
	count = compomentWidgetVector.size( );
	NumberVarTitleLineEdit **compomentArray;
	if( count && currentCom == nullptr ) {
		compomentArray = compomentWidgetVector.data( );
		for( index = 0; index < count; ++index )
			compomentArray[ index ]->setVarToLineEdit( ( uint64_t ) new_value );
	}
	currentCom = nullptr;
	emit value_change_signal( new_value );
}
BinCreateUnityNodeEditorScrollArea::BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainLayout = new QVBoxLayout( this );

	binScrollBarEditorWidget = addWigetToWidget< BinScrollBarEditorWidget >( this );
	decTitleLineEdit = addWigetToWidget< DecTitleLineEdit >( tr( "十进制:" ), UINT8_MAX, this );
	hexTitleLineEdit = addWigetToWidget< HexTitleLineEdit >( tr( "十六进制:" ), UINT8_MAX, this );
	octTitleLineEdit = addWigetToWidget< OctTitleLineEdit >( tr( "八进制:" ), UINT8_MAX, this );
	binTitleLineEdit = addWigetToWidget< BinTitleLineEdit >( tr( "二进制:" ), UINT8_MAX, this );

}
void BinCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
bool BinCreateUnityNodeEditorScrollArea::appendCompoment( UCompomentWidget *append_widget ) {
	if( append_widget == nullptr )
		return false;
	append_widget->setVarToLineEdit( ( uint64_t ) currentVar );
	mainLayout->addWidget( append_widget );
	compomentWidgetVector.emplace_back( append_widget );
	connect( append_widget, &UCompomentWidget::text_changed_signal, this, &BinCreateUnityNodeEditorScrollArea::textChanged_Slot );
	return true;
}
bool BinCreateUnityNodeEditorScrollArea::appendCompoment( ChangeBinValueWidget *append_widget ) {
	if( append_widget == nullptr )
		return false;
	append_widget->updateValue( currentVar );
	mainLayout->addWidget( append_widget );
	changeBinValueVector.emplace_back( append_widget );
	connect( append_widget, &ChangeBinValueWidget::value_change_signal, this, &BinCreateUnityNodeEditorScrollArea::valueChange_Slot );
	return true;
}
bool BinCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BinCreateUnityNodeEditorScrollArea::~BinCreateUnityNodeEditorScrollArea( ) {
	delete mainLayout;
	size_t count = changeBinValueVector.size( );
	size_t index;
	ChangeBinValueWidget **changeBinValueWidgetArray;
	if( count ) {
		changeBinValueWidgetArray = changeBinValueVector.data( );
		for( index = 0; index < count; ++index )
			delete changeBinValueWidgetArray[ index ];
		changeBinValueVector.clear( );
	}
	count = compomentWidgetVector.size( );
	NumberVarTitleLineEdit **compomentArray;
	if( count ) {
		compomentArray = compomentWidgetVector.data( );
		for( index = 0; index < count; ++index )
			delete compomentArray[ index ];
		changeBinValueVector.clear( );
	}
}
