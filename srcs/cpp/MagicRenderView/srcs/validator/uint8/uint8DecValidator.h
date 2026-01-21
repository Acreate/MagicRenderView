#ifndef UINT8DECVALIDATOR_H_H_HEAD__FILE__
#define UINT8DECVALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

#include "../validator.h"

class Uint8DecValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8DecValidator( QObject *parent );
	~Uint8DecValidator( ) override;
};
#endif // UINT8DECVALIDATOR_H_H_HEAD__FILE__
