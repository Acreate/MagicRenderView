#ifndef UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
#include "../validatorWidget.h"

class Uint8BinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Uint8BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
