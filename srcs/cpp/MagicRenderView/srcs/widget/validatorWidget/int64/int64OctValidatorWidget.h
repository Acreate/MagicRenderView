#ifndef INT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define INT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Int64OctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	Int64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // INT64OCTVALIDATORWIDGET_H_H_HEAD__FILE__
