#ifndef IMAGETOOLS_H_H_HEAD__FILE__
#define IMAGETOOLS_H_H_HEAD__FILE__


class QString;
class QImage;
namespace ImageTools {
	bool imageToBase64( const QImage &image, QString &result_hex, const QString &format_name );
	bool base64ToImage( const QString &base64, QImage &result_image, const QString &format_name );
	bool imageToBase64( const QImage &image, QString &result_hex );
	bool base64ToImage( const QString &base64, QImage &result_image );
};

#endif // IMAGETOOLS_H_H_HEAD__FILE__
