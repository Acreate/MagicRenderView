#include "doubleBinValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/double/doubleBinValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
DoubleBinValidatorWidget::DoubleBinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleBinValidator( this );
	lineEdit->setValidator( validator );
}
