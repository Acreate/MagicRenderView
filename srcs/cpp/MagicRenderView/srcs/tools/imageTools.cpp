#include "imageTools.h"

#include <QBuffer>
#include <QByteArray>
#include <QString>
#include <QImage>

bool ImageTools::imageToBase64( const QImage &image, QString &result_hex ) {
	return imageToBase64( image, result_hex, "PNG" );
}
bool ImageTools::base64ToImage( const QString &base64, QImage &result_image ) {
	return base64ToImage( base64, result_image, "PNG" );
}
bool ImageTools::imageToBase64( const QImage &image, QString &result_hex, const QString &format_name ) {
	QByteArray byteArray;
	QBuffer buffer( &byteArray );
	buffer.open( QIODevice::WriteOnly );
	if( image.save( &buffer, format_name.toLocal8Bit( ) ) == false )
		return false;
	result_hex = QString( byteArray.toBase64( ) );
	return true;
}
bool ImageTools::base64ToImage( const QString &base64, QImage &result_image, const QString &format_name ) {
	QByteArray byteArray = QByteArray::fromBase64( base64.toUtf8( ) );
	QBuffer buffer( &byteArray );
	return result_image.load( &buffer, format_name.toLocal8Bit( ) );
}
