#include "uInt64DecValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/uint64/uInt64DecValidator.h"
UInt64DecValidatorWidget::UInt64DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64DecValidator( this );
	lineEdit->setValidator( validator );
}
