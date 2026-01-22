#include "uInt64HexValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/uint64/uInt64HexValidator.h"
UInt64HexValidatorWidget::UInt64HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64HexValidator( this );
	lineEdit->setValidator( validator );
}
