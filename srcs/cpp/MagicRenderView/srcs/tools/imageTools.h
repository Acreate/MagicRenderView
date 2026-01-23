#ifndef IMAGETOOLS_H_H_HEAD__FILE__
#define IMAGETOOLS_H_H_HEAD__FILE__
#include <qbytearray.h>

class QColor;
class QString;
class QImage;
/// @brief 图像与颜色工具
namespace ImageTools {
	/// @brief 转换
	namespace conver {
		/// @brief 图像转换到16进制字符串
		/// @param image 图像
		/// @param result_hex 返回的16进制字符串
		/// @param format_name 转换格式
		/// @return 失败返回 false
		bool imageToBase64( const QImage &image, QString &result_hex, const QString &format_name );
		/// @brief 从16进制字符串转换到图像
		/// @param base64 十六进制字符串
		/// @param result_image 返回图像
		/// @param format_name 转换格式
		/// @return 失败返回 false
		bool base64ToImage( const QString &base64, QImage &result_image, const QString &format_name );
		/// @brief 图像转换到16进制字符串
		/// @param image 图像
		/// @param result_hex 返回的16进制字符串
		/// @return 失败返回 false
		bool imageToBase64( const QImage &image, QString &result_hex );
		/// @brief 从16进制字符串转换到图像
		/// @param base64 十六进制字符串
		/// @param result_image 返回图像
		/// @return 失败返回 false
		bool base64ToImage( const QString &base64, QImage &result_image );
		/// @brief 图像转二进制数据
		/// @param image 图像
		/// @param byte_array 返回二进制数据
		/// @param format_name 转换格式
		/// @return 失败返回 false
		bool imageToByteArray( const QImage &image, QByteArray &byte_array, const QString &format_name );
		/// @brief 二进制数据转换到图像
		/// @param byte_array 二进制数据
		/// @param result_image 返回图像
		/// @param format_name 转换格式
		/// @return 失败返回 false
		bool byteArrayToImage( const QByteArray &byte_array, QImage &result_image, const QString &format_name );
		/// @brief 图像转二进制数据
		/// @param image 图像
		/// @param byte_array 返回二进制数据
		/// @return 失败返回 false
		bool imageToByteArray( const QImage &image, QByteArray &byte_array );
		/// @brief 二进制数据转换到图像
		/// @param byte_array 二进制数据
		/// @param result_image 返回图像
		/// @return 失败返回 false
		bool byteArrayToImage( const QByteArray &byte_array, QImage &result_image );
	}
	/// @brief 颜色运算
	namespace colorOperation {
		/// @brief 颜色取模，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 取模失败返回 false
		bool mod( QColor &left_var, const QColor &right_var );
		/// @brief 颜色减法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 取模失败返回 false
		bool sub( QColor &left_var, const QColor &right_var );
		/// @brief 颜色加法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 取模失败返回 false
		bool add( QColor &left_var, const QColor &right_var );
		/// @brief 颜色除法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 取模失败返回 false
		bool div( QColor &left_var, const QColor &right_var );
		/// @brief 颜色乘法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 取模失败返回 false
		bool mul( QColor &left_var, const QColor &right_var );
		/// @brief 颜色取模，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param r 右操作数-红
		/// @param g 右操作数-绿
		/// @param b 右操作数-蓝
		/// @param a 右操作数-透明
		/// @return 取模失败返回 false
		bool mod( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		/// @brief 颜色减法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param r 右操作数-红
		/// @param g 右操作数-绿
		/// @param b 右操作数-蓝
		/// @param a 右操作数-透明
		/// @return 取模失败返回 false
		bool sub( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		/// @brief 颜色加法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param r 右操作数-红
		/// @param g 右操作数-绿
		/// @param b 右操作数-蓝
		/// @param a 右操作数-透明
		/// @return 取模失败返回 false
		bool add( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		/// @brief 颜色除法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param r 右操作数-红
		/// @param g 右操作数-绿
		/// @param b 右操作数-蓝
		/// @param a 右操作数-透明
		/// @return 取模失败返回 false
		bool div( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		/// @brief 颜色乘法，成功则改变左操作数
		/// @param left_var 左操作数
		/// @param r 右操作数-红
		/// @param g 右操作数-绿
		/// @param b 右操作数-蓝
		/// @param a 右操作数-透明
		/// @return 取模失败返回 false
		bool mul( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
	}
	namespace imageOperation {
		/// @brief 图像取模。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 成功返回 true
		bool mod( QImage &left_var, const QImage &right_var );
		/// @brief 图像减法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 成功返回 true
		bool sub( QImage &left_var, const QImage &right_var );
		/// @brief 图像加法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 成功返回 true
		bool add( QImage &left_var, const QImage &right_var );
		/// @brief 图像除法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 成功返回 true
		bool div( QImage &left_var, const QImage &right_var );
		/// @brief 图像乘法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @return 成功返回 true
		bool mul( QImage &left_var, const QImage &right_var );

		/// @brief 图像取模。
		/// @brief 该操作会改变左操作数当中匹配的值
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @param width 匹配宽度
		/// @param height 匹配高度
		/// @return 成功返回 true
		bool mod( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		/// @brief 图像减法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @param width 匹配宽度
		/// @param height 匹配高度
		/// @return 成功返回 true
		bool sub( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		/// @brief 图像加法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @param width 匹配宽度
		/// @param height 匹配高度
		/// @return 成功返回 true
		bool add( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		/// @brief 图像除法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @param width 匹配宽度
		/// @param height 匹配高度
		/// @return 成功返回 true
		bool div( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		/// @brief 图像乘法。
		/// @brief 该操作会改变左操作数当中匹配的值（两图像使用最小宽高进行像素运算）
		/// @param left_var 左操作数
		/// @param right_var 右操作数
		/// @param width 匹配宽度
		/// @param height 匹配高度
		/// @return 成功返回 true
		bool mul( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
	}
};

#endif // IMAGETOOLS_H_H_HEAD__FILE__
