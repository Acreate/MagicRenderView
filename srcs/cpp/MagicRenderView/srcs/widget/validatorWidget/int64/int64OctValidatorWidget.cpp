#include "int64OctValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/int64/int64OctValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
Int64OctValidatorWidget::Int64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64OctValidator( this );
	lineEdit->setValidator( validator );
}
