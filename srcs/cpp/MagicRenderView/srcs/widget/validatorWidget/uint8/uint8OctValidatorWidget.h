#ifndef UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Uint8OctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Uint8OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__
