#include "./combinationWidget.h"
CombinationWidget::CombinationWidget( const std_function<std_shared_ptr<IInfoWidgetStack>()> &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) { }
QString CombinationWidget::getText( ) const {
	return { };
}
bool CombinationWidget::setText( const QString &new_text ) const {
	return false;
}

void CombinationWidget::setPlaceholderText( const QString &placeholder_text ) const {
}
QString CombinationWidget::getPlaceholderText( ) const {
	return { };
}
