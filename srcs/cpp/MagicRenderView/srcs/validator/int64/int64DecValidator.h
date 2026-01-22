#ifndef INT64DECVALIDATOR_H_H_HEAD__FILE__
#define INT64DECVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class Int64DecValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Int64DecValidator( QObject *parent );
	~Int64DecValidator( ) override;
};
#endif // INT64DECVALIDATOR_H_H_HEAD__FILE__
