#ifndef UINT8VALIDATOR_H_H_HEAD__FILE__
#define UINT8VALIDATOR_H_H_HEAD__FILE__
#include <QValidator>

class Uint8Validator : public QValidator {
	Q_OBJECT;
public:
	Uint8Validator( QObject *parent )
		: QValidator( parent ) { }
	~Uint8Validator( ) override;
	State validate( QString &in_put, int &in_pos ) const override;
};

#endif // UINT8VALIDATOR_H_H_HEAD__FILE__
