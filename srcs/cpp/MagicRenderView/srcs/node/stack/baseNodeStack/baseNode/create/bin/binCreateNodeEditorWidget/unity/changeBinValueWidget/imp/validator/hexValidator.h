#ifndef HEXVALIDATOR_H_H_HEAD__FILE__
#define HEXVALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class HexValidator : public QValidator {
	Q_OBJECT;
protected:
	qsizetype maxLen;
public:
	HexValidator( QObject *parent );
	State validate( QString &input, int &pos ) const override;
};
#endif // HEXVALIDATOR_H_H_HEAD__FILE__
