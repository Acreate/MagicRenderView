#ifndef DOUBLEOCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define DOUBLEOCTVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class DoubleOctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	DoubleOctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // DOUBLEOCTVALIDATORWIDGET_H_H_HEAD__FILE__
