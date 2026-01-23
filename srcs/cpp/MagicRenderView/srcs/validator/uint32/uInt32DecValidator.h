#ifndef UINT32DECVALIDATOR_H_H_HEAD__FILE__
#define UINT32DECVALIDATOR_H_H_HEAD__FILE__


#include <validator/unSignedValidator.h>

class UInt32DecValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt32DecValidator( QObject *parent );
	~UInt32DecValidator( ) override;
};
#endif // UINT32DECVALIDATOR_H_H_HEAD__FILE__
