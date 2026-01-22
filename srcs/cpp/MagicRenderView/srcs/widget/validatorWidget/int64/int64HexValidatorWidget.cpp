#include "int64HexValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/int64/int64HexValidator.h"
Int64HexValidatorWidget::Int64HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64HexValidator( this );
	lineEdit->setValidator( validator );
}
