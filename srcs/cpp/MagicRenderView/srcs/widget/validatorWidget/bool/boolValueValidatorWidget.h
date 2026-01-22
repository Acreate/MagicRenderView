#ifndef BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class BoolValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	BoolValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
protected:
	bool eventFilter( QObject *watched, QEvent *event ) override;
};
#endif // BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
