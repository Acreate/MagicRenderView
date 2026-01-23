#ifndef UINT16HEXVALIDATOR_H_H_HEAD__FILE__
#define UINT16HEXVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt16HexValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt16HexValidator( QObject *parent );
	~UInt16HexValidator( ) override;
};
#endif // UINT16HEXVALIDATOR_H_H_HEAD__FILE__
