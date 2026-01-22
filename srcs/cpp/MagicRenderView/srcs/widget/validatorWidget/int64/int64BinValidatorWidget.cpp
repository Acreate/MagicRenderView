#include "int64BinValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/int64/int64BinValidator.h"
Int64BinValidatorWidget::Int64BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64BinValidator( this );
	lineEdit->setValidator( validator );
}
