#ifndef INT64BINVALIDATORWIDGET_H_H_HEAD__FILE__
#define INT64BINVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Int64BinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Int64BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // INT64BINVALIDATORWIDGET_H_H_HEAD__FILE__
