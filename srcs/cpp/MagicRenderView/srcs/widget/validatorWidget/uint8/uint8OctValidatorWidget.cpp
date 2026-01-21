#include "uint8OctValidatorWidget.h"

#include <QLineEdit>

#include <validator/uint8/uint8OctValidator.h>
Uint8OctValidatorWidget::Uint8OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8OctValidator( this );
	lineEdit->setValidator( validator );
}
