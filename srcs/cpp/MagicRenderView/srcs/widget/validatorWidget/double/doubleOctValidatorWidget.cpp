#include "doubleOctValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/double/doubleOctValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
DoubleOctValidatorWidget::DoubleOctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleOctValidator( this );
	lineEdit->setValidator( validator );
}
