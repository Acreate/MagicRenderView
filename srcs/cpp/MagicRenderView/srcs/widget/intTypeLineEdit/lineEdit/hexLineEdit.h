#ifndef HEXLINEEDIT_H_H_HEAD__FILE__
#define HEXLINEEDIT_H_H_HEAD__FILE__

#include <QLineEdit>

#include "numberVarLineEdit.h"
class HexLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	HexLineEdit( uint64_t value, QWidget *parent );
	bool toInt64( const QString &conver_text, int64_t &result_value ) const override;
	bool toUInt64( const QString &conver_text, uint64_t &result_value ) const override;
	
};

#endif // HEXLINEEDIT_H_H_HEAD__FILE__
