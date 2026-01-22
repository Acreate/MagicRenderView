#include "doubleValueValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/double/doubleValueValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
DoubleValueValidatorWidget::DoubleValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleValueValidator( this );
	lineEdit->setValidator( validator );
}
