#ifndef BINVALIDATOR_H_H_HEAD__FILE__
#define BINVALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class BinValidator : public QValidator {
	Q_OBJECT;
protected:
	qsizetype maxLen;
public:
	BinValidator( QObject *parent );
	State validate( QString &input, int &pos ) const override;
};
#endif // BINVALIDATOR_H_H_HEAD__FILE__
