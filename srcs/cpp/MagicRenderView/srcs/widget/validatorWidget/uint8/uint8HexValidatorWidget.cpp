#include "uint8HexValidatorWidget.h"

#include <QLineEdit>

#include <validator/uint8/uint8HexValidator.h>
Uint8HexValidatorWidget::Uint8HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8HexValidator( this );
	lineEdit->setValidator( validator );
}
