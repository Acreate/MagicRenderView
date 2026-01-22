#ifndef DOUBLEVALUEVALIDATOR_H_H_HEAD__FILE__
#define DOUBLEVALUEVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class DoubleValueValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	DoubleValueValidator( QObject *parent );
	~DoubleValueValidator( ) override;
};
#endif // DOUBLEVALUEVALIDATOR_H_H_HEAD__FILE__
