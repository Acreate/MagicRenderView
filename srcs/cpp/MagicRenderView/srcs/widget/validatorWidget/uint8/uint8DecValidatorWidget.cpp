#include "uint8DecValidatorWidget.h"

#include <QLineEdit>

#include <validator/uint8/uint8DecValidator.h>

Uint8DecValidatorWidget::Uint8DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8DecValidator( this );
	lineEdit->setValidator( validator );
}
