#ifndef UINT8BINVALIDATOR_H_H_HEAD__FILE__
#define UINT8BINVALIDATOR_H_H_HEAD__FILE__


#include <QValidator>

#include "../validator.h"

class Uint8BinValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8BinValidator( QObject *parent );
	~Uint8BinValidator( ) override;
};
#endif // UINT8BINVALIDATOR_H_H_HEAD__FILE__
