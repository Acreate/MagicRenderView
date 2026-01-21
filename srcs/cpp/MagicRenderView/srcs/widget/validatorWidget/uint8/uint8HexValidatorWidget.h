#ifndef UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__


#include "../validatorWidget.h"

class Uint8HexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Uint8HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__
