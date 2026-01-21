#ifndef BINVALIDATOR_H_H_HEAD__FILE__
#define BINVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class BinValidator : public Validator {
	Q_OBJECT;
public:
	BinValidator( uint64_t max_value, bool is_un_sign, QObject *parent )
		: Validator( max_value, 2, is_un_sign, parent ) { }
	bool checkCharValidator( QChar &check_char ) const override;
};

#endif // BINVALIDATOR_H_H_HEAD__FILE__
