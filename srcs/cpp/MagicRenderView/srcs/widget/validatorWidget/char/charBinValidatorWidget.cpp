#include "charBinValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/char/charBinValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharBinValidatorWidget::CharBinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharBinValidator( this );
	lineEdit->setValidator( validator );
}
