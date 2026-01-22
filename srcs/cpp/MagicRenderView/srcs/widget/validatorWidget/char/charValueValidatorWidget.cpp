#include "charValueValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/char/charValueValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharValueValidatorWidget::CharValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharValueValidator( this );
	lineEdit->setValidator( validator );
}
