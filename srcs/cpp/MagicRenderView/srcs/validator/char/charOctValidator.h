#ifndef CHAROCTVALIDATOR_H_H_HEAD__FILE__
#define CHAROCTVALIDATOR_H_H_HEAD__FILE__
#include <validator/signedValidator.h>

#include "../validator.h"

class CharOctValidator : public SignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharOctValidator( QObject *parent );
	~CharOctValidator( ) override;
};
#endif // CHAROCTVALIDATOR_H_H_HEAD__FILE__
