#include "doubleHexValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/double/doubleHexValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
DoubleHexValidatorWidget::DoubleHexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleHexValidator( this );
	lineEdit->setValidator( validator );
}
