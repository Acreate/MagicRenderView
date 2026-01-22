#ifndef STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#include "../validatorWidget.h"

class StringValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	StringValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
