#include "binCreateUnityNodeEditorScrollArea.h"

#include <QVBoxLayout>

#include "changeBinValueWidget/imp/binBinEditorWidget.h"
#include "changeBinValueWidget/imp/binDecimalEditorWidget.h"
#include "changeBinValueWidget/imp/binHexEditorWidget.h"
#include "changeBinValueWidget/imp/binOctEditorWidget.h"
#include "changeBinValueWidget/imp/binScrollBarEditorWidget.h"

void BinCreateUnityNodeEditorScrollArea::sycValue( uint8_t new_value ) {
	if( new_value == currentVar )
		return;
	currentVar = new_value;
	size_t count = changeBinValueVector.size( );
	auto changeBinValueWidgetArray = changeBinValueVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		changeBinValueWidgetArray[ index ]->updateValue( currentVar );
	emit value_change_signal( currentVar );
}
BinCreateUnityNodeEditorScrollArea::BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainLayout = new QVBoxLayout( this );
	binScrollBarEditorWidget = addWigetToWidget< BinScrollBarEditorWidget >( );
	binDecimalEditorWidget = addWigetToWidget< BinDecimalEditorWidget >( );
	binHexEditorWidget = addWigetToWidget< BinHexEditorWidget >( );
	binOctEditorWidget = addWigetToWidget< BinOctEditorWidget >( );
	binBinEditorWidget = addWigetToWidget< BinBinEditorWidget >( );

}
void BinCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
bool BinCreateUnityNodeEditorScrollArea::appendCompoment( ChangeBinValueWidget *append_widget ) {
	if( append_widget == nullptr )
		return false;
	append_widget->updateValue( currentVar );
	mainLayout->addWidget( append_widget );
	changeBinValueVector.emplace_back( append_widget );
	connect( append_widget, &ChangeBinValueWidget::value_change_signal, this, &BinCreateUnityNodeEditorScrollArea::sycValue );
	return true;
}
bool BinCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
BinCreateUnityNodeEditorScrollArea::~BinCreateUnityNodeEditorScrollArea( ) {
	delete binScrollBarEditorWidget;
	delete binBinEditorWidget;
	delete binOctEditorWidget;
	delete binHexEditorWidget;
	delete binDecimalEditorWidget;
}
