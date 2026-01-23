#ifndef VALIDATOR_H_H_HEAD__FILE__
#define VALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class Validator : public QValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t maxValue;
	int64_t minValue;
	uint64_t binSystem;
public:
	Validator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent );
	~Validator( ) override;
	virtual bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) = 0;
	virtual bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) = 0;
	void fixup( QString & result_change_text) const override;
};
#endif // VALIDATOR_H_H_HEAD__FILE__
