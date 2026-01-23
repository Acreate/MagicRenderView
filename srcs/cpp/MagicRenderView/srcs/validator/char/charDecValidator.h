#ifndef CHARDECVALIDATOR_H_H_HEAD__FILE__
#define CHARDECVALIDATOR_H_H_HEAD__FILE__

#include <validator/signedValidator.h>

#include "../validator.h"

class CharDecValidator : public SignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharDecValidator( QObject *parent );
	~CharDecValidator( ) override;
};
#endif // CHARDECVALIDATOR_H_H_HEAD__FILE__
