#ifndef CHARDECVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHARDECVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharDecValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	CharDecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHARDECVALIDATORWIDGET_H_H_HEAD__FILE__
