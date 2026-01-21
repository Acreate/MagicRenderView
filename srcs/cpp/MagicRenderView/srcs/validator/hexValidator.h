#ifndef HEXVALIDATOR_H_H_HEAD__FILE__
#define HEXVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class HexValidator : public Validator {
	Q_OBJECT;
public:
	HexValidator( uint64_t max_value, bool is_un_sign, QObject *parent )
		: Validator( max_value, 16, is_un_sign, parent ) { }
	bool checkCharValidator( QChar &check_char ) const override;
};
#endif // HEXVALIDATOR_H_H_HEAD__FILE__
