#ifndef DOUBLEVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define DOUBLEVALUEVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class DoubleValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	DoubleValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // DOUBLEVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
