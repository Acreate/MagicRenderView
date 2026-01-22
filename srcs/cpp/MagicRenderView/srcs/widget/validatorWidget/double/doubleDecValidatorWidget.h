#ifndef DOUBLEDECVALIDATORWIDGET_H_H_HEAD__FILE__
#define DOUBLEDECVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class DoubleDecValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	DoubleDecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // DOUBLEDECVALIDATORWIDGET_H_H_HEAD__FILE__
