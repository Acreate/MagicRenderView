#ifndef CHARVALUEVALIDATOR_H_H_HEAD__FILE__
#define CHARVALUEVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class CharValueValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharValueValidator( QObject *parent );
	~CharValueValidator( ) override;
	bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) override;
	State validate( QString &in_put, int &in_pos ) const override;
	bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) override;
};
#endif // CHARVALUEVALIDATOR_H_H_HEAD__FILE__
