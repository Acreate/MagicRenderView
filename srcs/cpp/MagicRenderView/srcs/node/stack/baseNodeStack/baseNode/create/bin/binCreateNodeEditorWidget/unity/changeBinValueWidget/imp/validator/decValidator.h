#ifndef DECVALIDATOR_H_H_HEAD__FILE__
#define DECVALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class DecValidator : public QValidator {
	Q_OBJECT;
protected:
	qsizetype maxLen;
public:
	DecValidator( QObject *parent );
	State validate( QString &input, int &pos ) const override;
};
#endif // DECVALIDATOR_H_H_HEAD__FILE__
