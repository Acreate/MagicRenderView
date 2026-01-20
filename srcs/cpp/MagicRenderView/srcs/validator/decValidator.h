#ifndef DECVALIDATOR_H_H_HEAD__FILE__
#define DECVALIDATOR_H_H_HEAD__FILE__
#include "validator.h"

class DecValidator : public Validator {
	Q_OBJECT;
public:
	DecValidator( uint64_t value, QObject *parent )
		: Validator(  parent ) {
		setMaxValue( value );
	}
	void setMaxValue( uint64_t value ) override;
	bool checkCharValidator( QChar &check_char ) const override;
};
#endif // DECVALIDATOR_H_H_HEAD__FILE__
