#ifndef UINT64BINVALIDATOR_H_H_HEAD__FILE__
#define UINT64BINVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt64BinValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt64BinValidator( QObject *parent );
	~UInt64BinValidator( ) override;
};
#endif // UINT64BINVALIDATOR_H_H_HEAD__FILE__
