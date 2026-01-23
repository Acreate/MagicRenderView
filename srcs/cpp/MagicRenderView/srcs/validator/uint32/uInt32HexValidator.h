#ifndef UINT32HEXVALIDATOR_H_H_HEAD__FILE__
#define UINT32HEXVALIDATOR_H_H_HEAD__FILE__


#include <validator/unSignedValidator.h>

class UInt32HexValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt32HexValidator( QObject *parent );
	~UInt32HexValidator( ) override;
};
#endif // UINT32HEXVALIDATOR_H_H_HEAD__FILE__
