#ifndef DOUBLEHEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define DOUBLEHEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class DoubleHexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	DoubleHexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // DOUBLEHEXVALIDATORWIDGET_H_H_HEAD__FILE__
