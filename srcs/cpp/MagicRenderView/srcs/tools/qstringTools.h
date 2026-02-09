#ifndef QSTRINGTOOLS_H_H_HEAD__FILE__
#define QSTRINGTOOLS_H_H_HEAD__FILE__

class QString;
namespace QStringTools {
	/// @brief 替换字符串
	/// @param org_string 原始字符串
	/// @param find_replace_string 原始字符串中查找的匹配字符串
	/// @param full_replace_string 匹配字符串替换成的目标字符串
	/// @param result_over_string 替换完成返回的字符串
	void replace( const QString &org_string, const QString &find_replace_string, const QString &full_replace_string, QString &result_over_string );
	/// @brief 替换字符串
	/// @param org_string 原始字符串
	/// @param find_replace_string 原始字符串中查找的匹配字符串
	/// @param full_replace_string 匹配字符串替换成的目标字符串
	/// @param replace_count 替换次数
	/// @param result_over_string 替换完成返回的字符串
	void replace( const QString &org_string, const QString &find_replace_string, const QString &full_replace_string, const size_t &replace_count, QString &result_over_string );
}

#endif // QSTRINGTOOLS_H_H_HEAD__FILE__
