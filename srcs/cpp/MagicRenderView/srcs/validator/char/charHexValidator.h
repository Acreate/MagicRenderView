#ifndef CHARHEXVALIDATOR_H_H_HEAD__FILE__
#define CHARHEXVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class CharHexValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharHexValidator( QObject *parent );
	~CharHexValidator( ) override;
};
#endif // CHARHEXVALIDATOR_H_H_HEAD__FILE__
