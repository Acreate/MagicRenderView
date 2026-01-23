#ifndef UINT32BINVALIDATOR_H_H_HEAD__FILE__
#define UINT32BINVALIDATOR_H_H_HEAD__FILE__


#include <validator/unSignedValidator.h>

class UInt32BinValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt32BinValidator( QObject *parent );
	~UInt32BinValidator( ) override;
};
#endif // UINT32BINVALIDATOR_H_H_HEAD__FILE__
