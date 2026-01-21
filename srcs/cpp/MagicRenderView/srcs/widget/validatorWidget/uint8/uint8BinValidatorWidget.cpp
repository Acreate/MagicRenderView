#include "uint8BinValidatorWidget.h"

#include <QLineEdit>
#include <validator/uint8/uint8BinValidator.h>
Uint8BinValidatorWidget::Uint8BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8BinValidator( this );
	lineEdit->setValidator( validator );
}
