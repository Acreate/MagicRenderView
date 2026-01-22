#include "charDecValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/char/charDecValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharDecValidatorWidget::CharDecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharDecValidator( this );
	lineEdit->setValidator( validator );
}
