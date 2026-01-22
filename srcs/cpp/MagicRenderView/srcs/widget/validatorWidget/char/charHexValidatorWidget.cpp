#include "charHexValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/char/charHexValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharHexValidatorWidget::CharHexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharHexValidator( this );
	lineEdit->setValidator( validator );
}
