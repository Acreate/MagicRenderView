#ifndef CHARBINVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHARBINVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharBinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	CharBinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHARBINVALIDATORWIDGET_H_H_HEAD__FILE__
