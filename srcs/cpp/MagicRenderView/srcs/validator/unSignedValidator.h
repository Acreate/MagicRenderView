#ifndef UNSIGNEDVALIDATOR_H_H_HEAD__FILE__
#define UNSIGNEDVALIDATOR_H_H_HEAD__FILE__

#include "validator.h"

class UnSignedValidator : public Validator {
	Q_OBJECT;
public:
	UnSignedValidator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent );
	~UnSignedValidator( ) override;
	bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) override;
	State validate( QString &in_put, int &in_pos ) const override;
	bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) override;
};
#endif // UNSIGNEDVALIDATOR_H_H_HEAD__FILE__
