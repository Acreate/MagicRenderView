#include "uInt64OctValidatorWidget.h"

#include <QLineEdit>

#include "../../../validator/uint64/uInt64OctValidator.h"
UInt64OctValidatorWidget::UInt64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64OctValidator( this );
	lineEdit->setValidator( validator );
}
