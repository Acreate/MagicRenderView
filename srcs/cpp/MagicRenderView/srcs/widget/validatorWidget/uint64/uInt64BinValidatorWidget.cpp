#include "uInt64BinValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/uint64/uInt64BinValidator.h"
UInt64BinValidatorWidget::UInt64BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64BinValidator( this );
	lineEdit->setValidator( validator );
}
