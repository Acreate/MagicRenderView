#ifndef DOUBLEBINVALIDATORWIDGET_H_H_HEAD__FILE__
#define DOUBLEBINVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class DoubleBinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	DoubleBinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // DOUBLEBINVALIDATORWIDGET_H_H_HEAD__FILE__
