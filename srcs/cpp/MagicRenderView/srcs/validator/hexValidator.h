#ifndef HEXVALIDATOR_H_H_HEAD__FILE__
#define HEXVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class HexValidator : public Validator {
	Q_OBJECT;
public:
	HexValidator( uint64_t value, QObject *parent )
		: Validator( parent ) {
		setMaxValue( value );
	}
	void setMaxValue( uint64_t value ) override;
	bool checkCharValidator( QChar &check_char ) const override;
};
#endif // HEXVALIDATOR_H_H_HEAD__FILE__
