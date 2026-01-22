#ifndef UINT64HEXVALIDATOR_H_H_HEAD__FILE__
#define UINT64HEXVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class UInt64HexValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt64HexValidator( QObject *parent );
	~UInt64HexValidator( ) override;
};
#endif // UINT64HEXVALIDATOR_H_H_HEAD__FILE__
