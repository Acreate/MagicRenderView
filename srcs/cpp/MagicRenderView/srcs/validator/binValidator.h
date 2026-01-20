#ifndef BINVALIDATOR_H_H_HEAD__FILE__
#define BINVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class BinValidator : public Validator {
	Q_OBJECT;
public:
	BinValidator( uint64_t value, QObject *parent )
		: Validator( parent ) {
		setMaxValue( value );
	}
	void setMaxValue( uint64_t value ) override;
	bool checkCharValidator( QChar &check_char ) const override;
};

#endif // BINVALIDATOR_H_H_HEAD__FILE__
