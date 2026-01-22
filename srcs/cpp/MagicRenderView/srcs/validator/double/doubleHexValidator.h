#ifndef DOUBLEHEXVALIDATOR_H_H_HEAD__FILE__
#define DOUBLEHEXVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class DoubleHexValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	DoubleHexValidator( QObject *parent );
	~DoubleHexValidator( ) override;
};
#endif // DOUBLEHEXVALIDATOR_H_H_HEAD__FILE__
