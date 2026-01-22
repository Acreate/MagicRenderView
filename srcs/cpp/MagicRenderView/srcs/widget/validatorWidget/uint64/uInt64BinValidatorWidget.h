#ifndef UINT64BINVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT64BINVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class UInt64BinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	UInt64BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT64BINVALIDATORWIDGET_H_H_HEAD__FILE__
