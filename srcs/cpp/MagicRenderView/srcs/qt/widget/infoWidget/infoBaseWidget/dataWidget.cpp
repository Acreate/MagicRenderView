#include "./dataWidget.h"

#include <QTextEdit>
#include <QVBoxLayout>

#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"
#include <qt/type/baseType/dataTypeObject.h>

#include "subWidget/hexEditor.h"
DataWidget::DataWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	dataTypeObject = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< DataTypeObject >( );

	edit = new HexEditor( this );
	mainLayout->addWidget( edit );
}
QString DataWidget::getText( ) const {
	return edit->toPlainText( );
}
void DataWidget::setText( const QString &new_text ) const {
}

void DataWidget::setPlaceholderText( const QString &placeholder_text ) const {
	edit->setPlaceholderText( placeholder_text );
}
QString DataWidget::getPlaceholderText( ) const {
	return edit->placeholderText( );
}
std_shared_ptr< ITypeObject > DataWidget::getValue( ) const {
	return dataTypeObject;
}
void DataWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );
	if( *element == nullptr )
		return;
}
