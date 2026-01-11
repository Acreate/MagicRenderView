#ifndef IMAGETOOLS_H_H_HEAD__FILE__
#define IMAGETOOLS_H_H_HEAD__FILE__

class QColor;
class QString;
class QImage;
namespace ImageTools {
	namespace conver {
		bool imageToBase64( const QImage &image, QString &result_hex, const QString &format_name );
		bool base64ToImage( const QString &base64, QImage &result_image, const QString &format_name );
		bool imageToBase64( const QImage &image, QString &result_hex );
		bool base64ToImage( const QString &base64, QImage &result_image );
	}
	namespace colorOperation {
		bool mod( QColor &left_var, const QColor &right_var );
		bool sub( QColor &left_var, const QColor &right_var );
		bool add( QColor &left_var, const QColor &right_var );
		bool div( QColor &left_var, const QColor &right_var );
		bool mul( QColor &left_var, const QColor &right_var );

		bool mod( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		bool sub( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		bool add( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		bool div( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
		bool mul( QColor &left_var, const int &r, const int &g, const int &b, const int &a );
	}
	namespace imageOperation {
		bool mod( QImage &left_var, const QImage &right_var );
		bool sub( QImage &left_var, const QImage &right_var );
		bool add( QImage &left_var, const QImage &right_var );
		bool div( QImage &left_var, const QImage &right_var );
		bool mul( QImage &left_var, const QImage &right_var );

		bool mod( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		bool sub( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		bool add( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		bool div( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
		bool mul( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height );
	}
};

#endif // IMAGETOOLS_H_H_HEAD__FILE__
