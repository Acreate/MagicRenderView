#include "./textWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
TextWidget::TextWidget( QWidget *parent, const QString &title_msg ): IInfoWidget( parent, title_msg ) {
	edit = new QLineEdit( this );
	mainLayout->addWidget( edit );
	edit->setPlaceholderText( title_msg );

	connect( edit, &QLineEdit::cursorPositionChanged, this, &TextWidget::cursorPositionChanged );
	connect( edit, &QLineEdit::editingFinished, this, &TextWidget::editingFinished );
	connect( edit, &QLineEdit::inputRejected, this, &TextWidget::inputRejected );
	connect( edit, &QLineEdit::returnPressed, this, &TextWidget::returnPressed );
	connect( edit, &QLineEdit::selectionChanged, this, &TextWidget::selectionChanged );
	connect( edit, &QLineEdit::textChanged, this, &TextWidget::textChanged );
	connect( edit, &QLineEdit::textEdited, this, &TextWidget::textEdited );
}
QString TextWidget::getText( ) const {
	return edit->text( );
}

void TextWidget::setText( const QString &new_text ) const {
	edit->setText( new_text );
}
void TextWidget::setTitle( const QString &new_title ) const {
	title->setText( new_title );
}

QString TextWidget::getPlaceholderText( ) const {
	return edit->placeholderText( );
}
void TextWidget::setPlaceholderText( const QString &placeholder_text ) const {
	edit->setPlaceholderText( placeholder_text );
}
