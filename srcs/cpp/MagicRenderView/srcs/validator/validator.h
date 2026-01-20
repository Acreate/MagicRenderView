#ifndef VALIDATOR_H_H_HEAD__FILE__
#define VALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class Validator : public QValidator {
	Q_OBJECT;
protected:
	qsizetype maxLen;
public:
	Validator( QObject *parent ) : QValidator( parent ) { }
	virtual void setMaxValue( uint64_t value ) = 0;
	virtual qsizetype getMaxLen( ) const { return maxLen; }
	virtual bool checkCharValidator( QChar &check_char ) const = 0;
	State validate( QString &input, int &pos ) const override;
};
#endif // VALIDATOR_H_H_HEAD__FILE__
