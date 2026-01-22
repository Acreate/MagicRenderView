#ifndef CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharHexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	CharHexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__
