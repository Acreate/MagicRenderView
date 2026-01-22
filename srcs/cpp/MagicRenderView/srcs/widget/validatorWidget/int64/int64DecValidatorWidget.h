#ifndef INT64DECVALIDATORWIDGET_H_H_HEAD__FILE__
#define INT64DECVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Int64DecValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Int64DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // INT64DECVALIDATORWIDGET_H_H_HEAD__FILE__
