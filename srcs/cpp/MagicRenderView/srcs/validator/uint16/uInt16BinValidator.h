#ifndef UINT16BINVALIDATOR_H_H_HEAD__FILE__
#define UINT16BINVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt16BinValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt16BinValidator( QObject *parent );
	~UInt16BinValidator( ) override;
};
#endif // UINT16BINVALIDATOR_H_H_HEAD__FILE__
