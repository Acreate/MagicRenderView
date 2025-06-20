#include "./IInfoWidget.h"

#include <QLabel>
#include <QVBoxLayout>

#include "../../stack/infoWidgetStack/IInfoWidgetStack.h"
#include "../../stack/infoWidgetStack/base/baseInfoWidgetStack.h"

IInfoWidget::IInfoWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): QWidget( parent ), getStackFunction( get_stack_function ) {
	if( !getStackFunction )
		getStackFunction = [] {
			return IInfoWidgetStack::getStdSharedPtrInstance< BaseInfoWidgetStack >( );
		};
	infoWidgetSharedStack = getStackFunction( );
	mainLayout = new QVBoxLayout( this );
	title = new QLabel( this );
	mainLayout->addWidget( title );
}
QString IInfoWidget::getTitle( ) const {
	return title->text( );
}
