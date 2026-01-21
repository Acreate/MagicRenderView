#ifndef OCTVALIDATOR_H_H_HEAD__FILE__
#define OCTVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class OctValidator : public Validator {
	Q_OBJECT;
public:
	OctValidator( uint64_t max_value,  bool is_un_sign, QObject *parent )
		: Validator( max_value, 8, is_un_sign, parent ) {
	}
	bool checkCharValidator( QChar &check_char ) const override;
};

#endif // OCTVALIDATOR_H_H_HEAD__FILE__
