#include "int64DecValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/int64/int64DecValidator.h"
Int64DecValidatorWidget::Int64DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64DecValidator( this );
	lineEdit->setValidator( validator );
}
