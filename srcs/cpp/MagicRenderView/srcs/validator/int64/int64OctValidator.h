#ifndef INT64OCTVALIDATOR_H_H_HEAD__FILE__
#define INT64OCTVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class Int64OctValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Int64OctValidator( QObject *parent );
	~Int64OctValidator( ) override;
};
#endif // INT64OCTVALIDATOR_H_H_HEAD__FILE__
