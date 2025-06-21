#include "./errorMsgWidget.h"

#include <QLabel>
#include <QVBoxLayout>

ErrorMsgWidget::ErrorMsgWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &error_msg ): IInfoWidget( get_stack_function, parent, error_msg ), text( new QString ), placeholder( new QString ) {
}
void ErrorMsgWidget::setText( const QString &new_text ) const {
	*text = new_text;
	title->setToolTip( QString( "注意:%1\n建议:%2" ).arg( *text ).arg( *placeholder ) );
}

void ErrorMsgWidget::setPlaceholderText( const QString &placeholder_text ) const {
	*placeholder = placeholder_text;
	title->setToolTip( QString( "注意:%1\n建议:%2" ).arg( *text ).arg( *placeholder ) );
}
void ErrorMsgWidget::mouseMoveEvent( QMouseEvent *event ) {
	IInfoWidget::mouseMoveEvent( event );
}
