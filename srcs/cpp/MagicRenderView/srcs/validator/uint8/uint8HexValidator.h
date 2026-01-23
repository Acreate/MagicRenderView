#ifndef UINT8HEXVALIDATOR_H_H_HEAD__FILE__
#define UINT8HEXVALIDATOR_H_H_HEAD__FILE__
#include <validator/unSignedValidator.h>

class Uint8HexValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8HexValidator( QObject *parent );
	~Uint8HexValidator( ) override;
};
#endif // UINT8HEXVALIDATOR_H_H_HEAD__FILE__
