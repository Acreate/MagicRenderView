#include "scrollValueChangeWidget.h"

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>
void ScrollValueChangeWidget::scrollValueChange( int value ) {
	if( binOr == value )
		return;
	valueTitile->setText( tr( "值:%1" ).arg( value, maxLen, 10, '0' ) );
	binOr = value;
	emit value_change_signal( this, value );
}
ScrollValueChangeWidget::ScrollValueChangeWidget( int64_t min_value, size_t max_value, QWidget *parent ) {
	maxLen = tr( "%1" ).arg( max_value, 0, 10 ).length( );

	scrollWidget = new QWidget( this );
	scrollWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	scrollWidgetLayout = new QHBoxLayout( scrollWidget );
	scrollBar = new QScrollBar( Qt::Horizontal, scrollWidget );
	scrollBar->setMaximum( max_value );
	scrollBar->setMinimum( min_value );
	scrollBar->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	scrollBarTitile = new QLabel( tr( "滑动改变值" ), scrollWidget );
	scrollWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	scrollWidgetLayout->setSpacing( 0 );
	scrollWidgetLayout->addWidget( scrollBarTitile );
	scrollWidgetLayout->addWidget( scrollBar );

	valueTitile = new QLabel( tr( "值:%1" ).arg( 0, maxLen, 10, '0' ), this );
	mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( valueTitile );
	mainLayout->addWidget( scrollWidget );

	connect( scrollBar, &QScrollBar::valueChanged, this, &ScrollValueChangeWidget::scrollValueChange );
}
void ScrollValueChangeWidget::updateValue( uint8_t new_value ) {
	scrollBar->setValue( new_value );
	valueTitile->setText( tr( "值:%1" ).arg( new_value, maxLen, 10, '0' ) );
}
