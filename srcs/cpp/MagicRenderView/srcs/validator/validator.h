#ifndef VALIDATOR_H_H_HEAD__FILE__
#define VALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class Validator : public QValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t maxValue;
	uint64_t binSystem;
public:
	Validator( uint64_t max_value, uint64_t bin_system, QObject *parent );
	~Validator( ) override;
	State validate( QString &in_put, int &in_pos ) const override;
	virtual bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt );
	virtual bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text );
};
#endif // VALIDATOR_H_H_HEAD__FILE__
