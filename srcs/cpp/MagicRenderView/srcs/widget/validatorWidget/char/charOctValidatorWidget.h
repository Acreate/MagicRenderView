#ifndef CHAROCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHAROCTVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharOctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	CharOctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHAROCTVALIDATORWIDGET_H_H_HEAD__FILE__
