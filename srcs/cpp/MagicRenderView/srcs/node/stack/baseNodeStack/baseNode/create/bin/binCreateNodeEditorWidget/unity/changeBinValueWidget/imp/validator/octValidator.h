#ifndef OCTVALIDATOR_H_H_HEAD__FILE__
#define OCTVALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class OctValidator : public QValidator {
	Q_OBJECT;
protected:
	qsizetype maxLen;
public:
	OctValidator( QObject *parent );
	State validate( QString &input, int &pos ) const override;
};

#endif // OCTVALIDATOR_H_H_HEAD__FILE__
