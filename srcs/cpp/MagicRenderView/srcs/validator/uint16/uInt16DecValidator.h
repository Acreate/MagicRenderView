#ifndef UINT16DECVALIDATOR_H_H_HEAD__FILE__
#define UINT16DECVALIDATOR_H_H_HEAD__FILE__



#include <validator/unSignedValidator.h>

class UInt16DecValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt16DecValidator( QObject *parent );
	~UInt16DecValidator( ) override;
};
#endif // UINT16DECVALIDATOR_H_H_HEAD__FILE__
