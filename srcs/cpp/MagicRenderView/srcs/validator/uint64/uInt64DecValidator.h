#ifndef UINT64DECVALIDATOR_H_H_HEAD__FILE__
#define UINT64DECVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt64DecValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt64DecValidator( QObject *parent );
	~UInt64DecValidator( ) override;
};
#endif // UINT64DECVALIDATOR_H_H_HEAD__FILE__
