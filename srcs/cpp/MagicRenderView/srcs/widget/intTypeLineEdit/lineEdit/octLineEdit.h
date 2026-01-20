#ifndef OCTLINEEDIT_H_H_HEAD__FILE__
#define OCTLINEEDIT_H_H_HEAD__FILE__

#include "numberVarLineEdit.h"
class OctLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	OctLineEdit( uint64_t value, QWidget *parent );
	bool toInt64( const QString &conver_text, int64_t &result_value ) const override;
	bool toUInt64( const QString &conver_text, uint64_t &result_value ) const override;

};

#endif // OCTLINEEDIT_H_H_HEAD__FILE__
