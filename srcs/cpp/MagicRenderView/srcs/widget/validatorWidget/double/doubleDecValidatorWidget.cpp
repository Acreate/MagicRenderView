#include "doubleDecValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/double/doubleDecValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
DoubleDecValidatorWidget::DoubleDecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleDecValidator( this );
	lineEdit->setValidator( validator );
}
