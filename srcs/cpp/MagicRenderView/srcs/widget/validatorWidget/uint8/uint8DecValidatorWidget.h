#ifndef UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Uint8DecValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Uint8DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__
