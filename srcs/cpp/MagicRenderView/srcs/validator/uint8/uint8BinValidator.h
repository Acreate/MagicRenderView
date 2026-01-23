#ifndef UINT8BINVALIDATOR_H_H_HEAD__FILE__
#define UINT8BINVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class Uint8BinValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8BinValidator( QObject *parent );
	~Uint8BinValidator( ) override;
};
#endif // UINT8BINVALIDATOR_H_H_HEAD__FILE__
