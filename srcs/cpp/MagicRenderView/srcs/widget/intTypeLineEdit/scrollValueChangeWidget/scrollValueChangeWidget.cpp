#include "scrollValueChangeWidget.h"

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>

void ScrollValueChangeWidget::scrollToTitleValue( uint64_t value ) {
	valueTitile->setText( tr( "值:%1" ).arg( value ) );
}
void ScrollValueChangeWidget::scrollToTitleValue( int64_t value ) {
	valueTitile->setText( tr( "值:%1" ).arg( value ) );
}
ScrollValueChangeWidget::ScrollValueChangeWidget( QWidget *parent ) : QWidget( parent ) {

	scrollWidget = new QWidget( this );
	scrollWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	scrollWidgetLayout = new QHBoxLayout( scrollWidget );
	scrollBar = new QScrollBar( Qt::Horizontal, scrollWidget );
	scrollBar->setMaximum( 100 );
	scrollBar->setMinimum( 0 );
	scrollBar->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
	scrollBarTitile = new QLabel( tr( "滑动改变值" ), scrollWidget );
	scrollWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	scrollWidgetLayout->setSpacing( 0 );
	scrollWidgetLayout->addWidget( scrollBarTitile );
	scrollWidgetLayout->addWidget( scrollBar );

	valueTitile = new QLabel( tr( "值:%1" ).arg( 0 ), this );
	mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( valueTitile );
	mainLayout->addWidget( scrollWidget );

	connect( scrollBar, &QScrollBar::valueChanged, this, &ScrollValueChangeWidget::value_change_signal );
}
void ScrollValueChangeWidget::scrollToPoint( double value, double min_var, double max_var ) {
	value = value - min_var;
	max_var = max_var - min_var;
	min_var = 100 / max_var;
	value = value * min_var;
	scrollBar->setValue( value );
}
