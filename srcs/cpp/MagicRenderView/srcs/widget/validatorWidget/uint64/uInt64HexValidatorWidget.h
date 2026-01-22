#ifndef UINT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class UInt64HexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	UInt64HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__
