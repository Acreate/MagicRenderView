#include "charOctValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/char/charOctValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharOctValidatorWidget::CharOctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharOctValidator( this );
	lineEdit->setValidator( validator );
}
