#ifndef DECVALIDATOR_H_H_HEAD__FILE__
#define DECVALIDATOR_H_H_HEAD__FILE__
#include "validator.h"

class DecValidator : public Validator {
	Q_OBJECT;
public:
	DecValidator( uint64_t max_value, bool is_un_sign, QObject *parent )
		: Validator( max_value, 10, is_un_sign, parent ) { }
	bool checkCharValidator( QChar &check_char ) const override;
};
#endif // DECVALIDATOR_H_H_HEAD__FILE__
