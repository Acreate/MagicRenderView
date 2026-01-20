#include "binScrollBarEditorWidget.h"

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>
void BinScrollBarEditorWidget::scrollValueChange( int value ) {
	if( binOr == value )
		return;
	valueTitile->setText( tr( "值:%1" ).arg( value, maxLen, 10, '0' ) );
	binOr = value;
	emit value_change_signal( this, value );
}
BinScrollBarEditorWidget::BinScrollBarEditorWidget( BinCreateUnityNodeEditorScrollArea *bin_create_unity_node_editor_scroll_area ) : ChangeBinValueWidget( bin_create_unity_node_editor_scroll_area ) {
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 10 ).length( );

	scrollWidget = new QWidget( this );
	scrollWidgetLayout = new QHBoxLayout( scrollWidget );
	scrollBar = new QScrollBar( Qt::Horizontal, scrollWidget );
	scrollBar->setMaximum( UINT8_MAX );
	scrollBar->setMinimum( 0 );
	scrollBarTitile = new QLabel( tr( "滑动改变值" ), scrollWidget );
	scrollWidgetLayout->addWidget( scrollBarTitile );
	scrollWidgetLayout->addWidget( scrollBar );

	valueTitile = new QLabel( tr( "值:%1" ).arg( 0, maxLen, 10, '0' ), this );
	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( valueTitile );
	mainLayout->addWidget( scrollWidget );

	connect( scrollBar, &QAbstractSlider::valueChanged, this, &BinScrollBarEditorWidget::scrollValueChange );
}
void BinScrollBarEditorWidget::updateValue( uint8_t new_value ) {
	scrollBar->setValue( new_value );
	valueTitile->setText( tr( "值:%1" ).arg( new_value, maxLen, 10, '0' ) );
}
