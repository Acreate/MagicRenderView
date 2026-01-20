#ifndef OCTVALIDATOR_H_H_HEAD__FILE__
#define OCTVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class OctValidator : public Validator {
	Q_OBJECT;
public:
	OctValidator( uint64_t value, QObject *parent )
		: Validator( parent ) {
		setMaxValue( value );
	}
	void setMaxValue( uint64_t value ) override;
	bool checkCharValidator( QChar &check_char ) const override;
};

#endif // OCTVALIDATOR_H_H_HEAD__FILE__
