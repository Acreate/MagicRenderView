#ifndef UINT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class UInt64OctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	UInt64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__
