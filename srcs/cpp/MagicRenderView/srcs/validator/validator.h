#ifndef VALIDATOR_H_H_HEAD__FILE__
#define VALIDATOR_H_H_HEAD__FILE__

#include <QValidator>

class Validator : public QValidator {
	Q_OBJECT;
public:
	/// @brief 最大值
	uint64_t maxValue;
	/// @brief 最大长度
	uint64_t maxLen;
	/// @brief 进制
	uint64_t binSystem;
	/// @brief 是否带符号
	bool isUnSign;
	/// @brief 输入整数的存储
	union Value {
		uint64_t uint64Value;
		int64_t int64Value;
	};
	/// @brief 值
	Value *value;
protected:
	virtual bool normalInput( QString &input, int &pos ) const;
	virtual bool normalInputLen( QString &input, int &pos ) const;
public:
	Validator( uint64_t max_value, uint64_t bin_system, bool is_un_sign, QObject *parent );
	~Validator( ) override;
	virtual uint64_t getMaxValue( ) const { return maxValue; }
	virtual uint64_t getBinSystem( ) const { return binSystem; }
	virtual bool toUInt64( const QString &conver_text, uint64_t &result_uint64_value ) const;
	virtual bool toInt64( const QString &conver_text, int64_t &result_uint64_value ) const;
	virtual uint64_t getUInt64Var( ) const { return value->uint64Value; }
	virtual int64_t getInt64Var( ) const { return value->int64Value; }
	virtual bool getUnSignStatus( ) const { return isUnSign; }
	virtual uint64_t getMaxLen( ) const { return maxLen; }
	virtual bool varToString( const int64_t &var, QString &result_conver_string );
	virtual bool varToString( const uint64_t &var, QString &result_conver_string );
	/// @brief 检查值，该函数决定是否进行数据重置
	/// @param check_char 值符号
	/// @return 失败返回 false，并且由 validate 进行重置
	virtual bool checkCharValidator( QChar &check_char ) const = 0;
	/// @brief 检查符号，该函数由 isUnSign 决定是否调用
	/// @brief 当 isUnSign 为 true 时，调用该函数
	/// @brief 与 checkCharValidator 同样，决定是否进行数据重置
	/// @param check_char 检查的符号
	/// @return 失败返回 false，并且由 validate 进行重置
	virtual bool checkCharSignValidator( QChar &check_char ) const;
	/// @brief 用于检查整个输入是否正确
	/// @param input 输入字符串
	/// @param check_len 检查长度
	/// @param result_index 最后检查位置
	/// @return 失败返回 false
	virtual bool chenckAllInput( QChar *input, qsizetype check_len, qsizetype &result_index ) const;
	State validate( QString &input, int &pos ) const override;
};
#endif // VALIDATOR_H_H_HEAD__FILE__
