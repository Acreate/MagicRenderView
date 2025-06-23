#include "./vectorWidget.h"
VectorWidget::VectorWidget( const std_function<std_shared_ptr<IInfoWidgetStack>()> &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) { }
QString VectorWidget::getText( ) const {
	return { };
}
bool VectorWidget::setText( const QString &new_text ) const {
	return false;
}

void VectorWidget::setPlaceholderText( const QString &placeholder_text ) const {
}
QString VectorWidget::getPlaceholderText( ) const {
	return { };
}
