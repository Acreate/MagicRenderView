#include "binCreateUnityNodeEditorScrollArea.h"

#include <QVBoxLayout>
#include <widget/intTypeLineEdit/titleLineEdit/binTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/decTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/hexTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/numberVarTitleLineEdit.h>
#include <widget/intTypeLineEdit/titleLineEdit/octTitleLineEdit.h>

#include <widget/intTypeLineEdit/lineEdit/numberVarLineEdit.h>

#include "../../../../../../../../widget/intTypeLineEdit/scrollValueChangeWidget/scrollValueChangeWidget.h"

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
	if( signalScroll != nullptr ) {
		signalScroll->scrollToPoint( newValue, 0, UINT8_MAX );
		signalScroll = nullptr;
	}
	scrollValueChangeWidget->scrollToTitleValue( ( int64_t ) newValue );
	emit value_change_signal( 0 );
}
void BinCreateUnityNodeEditorScrollArea::valueChange_Slot( int curren_scroll_bar_point ) {
	size_t count;
	size_t index;
	count = compomentWidgetVector.size( );
	NumberVarTitleLineEdit **compomentArray;
	double new_value = UINT8_MAX * curren_scroll_bar_point / 100;
	if( count && currentCom == nullptr ) {
		compomentArray = compomentWidgetVector.data( );
		for( index = 0; index < count; ++index )
			compomentArray[ index ]->setVarToLineEdit( ( uint64_t ) new_value );
	}
	currentCom = nullptr;
	signalScroll = scrollValueChangeWidget;
	scrollValueChangeWidget->scrollToTitleValue( ( int64_t ) new_value );
	emit value_change_signal( new_value );
}
BinCreateUnityNodeEditorScrollArea::BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	signalScroll = nullptr;
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

	scrollValueChangeWidget = new ScrollValueChangeWidget( mainWidget );

	scrollValueChangeWidget->scrollToTitleValue( ( int64_t ) currentVar );
	scrollValueChangeWidget->scrollToPoint( currentVar, 0, UINT8_MAX );

	mainLayout->addWidget( scrollValueChangeWidget );
	connect( scrollValueChangeWidget, &ScrollValueChangeWidget::value_change_signal, this, &BinCreateUnityNodeEditorScrollArea::valueChange_Slot );

	decTitleLineEdit = addWigetToWidget< DecTitleLineEdit >( tr( "十进制:" ), UINT8_MAX, true, mainWidget );
	hexTitleLineEdit = addWigetToWidget< HexTitleLineEdit >( tr( "十六进制:" ), UINT8_MAX, true, mainWidget );
	octTitleLineEdit = addWigetToWidget< OctTitleLineEdit >( tr( "八进制:" ), UINT8_MAX, true, mainWidget );
	binTitleLineEdit = addWigetToWidget< BinTitleLineEdit >( tr( "二进制:" ), UINT8_MAX, true, mainWidget );

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

bool BinCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BinCreateUnityNodeEditorScrollArea::~BinCreateUnityNodeEditorScrollArea( ) {
	delete mainLayout;
	size_t count;
	size_t index;
	delete scrollValueChangeWidget;

	count = compomentWidgetVector.size( );
	NumberVarTitleLineEdit **compomentArray;
	if( count ) {
		compomentArray = compomentWidgetVector.data( );
		for( index = 0; index < count; ++index )
			delete compomentArray[ index ];
		compomentWidgetVector.clear( );
	}
}
