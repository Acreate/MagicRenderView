#ifndef SIGNEDVALIDATOR_H_H_HEAD__FILE__
#define SIGNEDVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class SignedValidator : public Validator {
	Q_OBJECT;
protected:
	union Type64Bit {
		int64_t int64TypeVar;
		uint64_t uint64TypeVar;
		double doubleTypeVar;
	};
public:
	SignedValidator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent );
	~SignedValidator( ) override;
	bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) override;
	State validate( QString &in_put, int &in_pos ) const override;
	bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) override;
};
#endif // SIGNEDVALIDATOR_H_H_HEAD__FILE__
