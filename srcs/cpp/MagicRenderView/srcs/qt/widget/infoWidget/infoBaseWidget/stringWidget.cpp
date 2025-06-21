#include "./stringWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include <qt/stack/varStack/IVarStack.h>
#include <qt/stack/varStack/base/baseVarStackEx.h>

#include <qt/type/baseType/stringTypeObject.h>
StringWidget::StringWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	editString = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< StringTypeObject >( );

	QWidget *btnWidget = new QWidget( this );
	QHBoxLayout *btnLayout = new QHBoxLayout( btnWidget );
	mainLayout->addWidget( btnWidget );

	QPushButton *saveBtn = new QPushButton( this );
	btnLayout->addWidget( saveBtn );
	saveBtn->setText( "保存" );
	connect( saveBtn, &QPushButton::clicked, [this] {
		editString->setString( textEdit->toPlainText( ) );
		emit valueChanged( );
	} );

	QPushButton *clearBtn = new QPushButton( this );
	btnLayout->addWidget( clearBtn );
	clearBtn->setText( "清理" );
	connect( clearBtn, &QPushButton::clicked, [this] {
		textEdit->clear( );
		editString->setString( "" );
		emit valueChanged( );
	} );

	textEdit = new QTextEdit( this );
	textEdit->setMinimumHeight( 100 );
	mainLayout->addWidget( textEdit );
}
StringWidget::~StringWidget( ) {
}
QString StringWidget::getText( ) const {
	return textEdit->toPlainText( );
}
void StringWidget::setText( const QString &new_text ) const {
	textEdit->setPlainText( new_text );
	editString->setString( new_text );
}

void StringWidget::setPlaceholderText( const QString &placeholder_text ) const {
	textEdit->setPlaceholderText( placeholder_text );
}
QString StringWidget::getPlaceholderText( ) const {
	return textEdit->placeholderText( );
}
std_shared_ptr< ITypeObject > StringWidget::getValue( ) const {
	return editString;
}
void StringWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	if( *value != nullptr ) {
		QString string = value->toString( );
		editString->setString( string );
		textEdit->setText( string );
	}
}
