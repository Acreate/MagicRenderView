#include "imageTools.h"

#include <QBuffer>
#include <QByteArray>
#include <QString>
#include <QImage>
#include <QColor>

bool ImageTools::conver::imageToBase64( const QImage &image, QString &result_hex ) {
	return imageToBase64( image, result_hex, "PNG" );
}
bool ImageTools::conver::base64ToImage( const QString &base64, QImage &result_image ) {
	return base64ToImage( base64, result_image, "PNG" );
}
bool ImageTools::conver::imageToByteArray( const QImage &image, QByteArray &byte_array, const QString &format_name ) {
	QBuffer buffer( &byte_array );
	buffer.open( QIODevice::WriteOnly );
	if( image.save( &buffer, format_name.toLocal8Bit( ) ) == false )
		return false;
	return true;
}
bool ImageTools::conver::byteArrayToImage( const QByteArray &byte_array, QImage &result_image, const QString &format_name ) {
	QByteArray byteArray = byte_array;
	QBuffer buffer( &byteArray );
	return result_image.load( &buffer, format_name.toLocal8Bit( ) );
}
bool ImageTools::conver::imageToByteArray( const QImage &image, QByteArray &byte_array ) {
	return imageToByteArray( image, byte_array, "PNG" );
}
bool ImageTools::conver::byteArrayToImage( const QByteArray &byte_array, QImage &result_image ) {
	return byteArrayToImage( byte_array, result_image, "PNG" );
}
bool ImageTools::conver::imageToBase64( const QImage &image, QString &result_hex, const QString &format_name ) {
	QByteArray byteArray;
	QBuffer buffer( &byteArray );
	buffer.open( QIODevice::WriteOnly );
	if( image.save( &buffer, format_name.toLocal8Bit( ) ) == false )
		return false;
	result_hex = QString( byteArray.toBase64( ) );
	return true;
}
bool ImageTools::conver::base64ToImage( const QString &base64, QImage &result_image, const QString &format_name ) {
	QByteArray byteArray = QByteArray::fromBase64( base64.toUtf8( ) );
	QBuffer buffer( &byteArray );
	return result_image.load( &buffer, format_name.toLocal8Bit( ) );
}

bool ImageTools::colorOperation::mod( QColor &left_var, const QColor &right_var ) {
	int red = right_var.red( );
	int green = right_var.green( );
	int blue = right_var.blue( );
	int alpha = right_var.alpha( );
	left_var = QColor( red ? left_var.red( ) % red : 0, green ? left_var.green( ) % green : 0, blue ? left_var.blue( ) % blue : 0, alpha ? left_var.alpha( ) % alpha : 0 );
	return true;
}
bool ImageTools::colorOperation::sub( QColor &left_var, const QColor &right_var ) {
	int red = right_var.red( );
	int green = right_var.green( );
	int blue = right_var.blue( );
	int alpha = right_var.alpha( );
	left_var = QColor( left_var.red( ) - red, left_var.green( ) - green, left_var.blue( ) - blue, left_var.alpha( ) - alpha );
	return true;
}
bool ImageTools::colorOperation::add( QColor &left_var, const QColor &right_var ) {
	int red = right_var.red( );
	int green = right_var.green( );
	int blue = right_var.blue( );
	int alpha = right_var.alpha( );
	left_var = QColor( left_var.red( ) + red, left_var.green( ) + green, left_var.blue( ) + blue, left_var.alpha( ) + alpha );
	return true;
}
bool ImageTools::colorOperation::div( QColor &left_var, const QColor &right_var ) {
	int red = right_var.red( );
	int green = right_var.green( );
	int blue = right_var.blue( );
	int alpha = right_var.alpha( );
	left_var = QColor( red ? left_var.red( ) / red : 0, green ? left_var.green( ) / green : 0, blue ? left_var.blue( ) / blue : 0, alpha ? left_var.alpha( ) / alpha : 0 );
	return true;
}
bool ImageTools::colorOperation::mul( QColor &left_var, const QColor &right_var ) {
	int red = right_var.red( );
	int green = right_var.green( );
	int blue = right_var.blue( );
	int alpha = right_var.alpha( );
	left_var = QColor( red ? left_var.red( ) * red : 0, green ? left_var.green( ) * green : 0, blue ? left_var.blue( ) * blue : 0, alpha ? left_var.alpha( ) * alpha : 0 );
	return true;
}

bool ImageTools::colorOperation::mod( QColor &left_var, const int &r, const int &g, const int &b, const int &a ) {
	left_var = QColor( r ? left_var.red( ) % r : 0, g ? left_var.green( ) % g : 0, b ? left_var.blue( ) % b : 0, a ? left_var.alpha( ) % a : 0 );
	return true;
}
bool ImageTools::colorOperation::sub( QColor &left_var, const int &r, const int &g, const int &b, const int &a ) {
	left_var = QColor( left_var.red( ) - r, left_var.green( ) - g, left_var.blue( ) - b, left_var.alpha( ) - a );
	return true;
}
bool ImageTools::colorOperation::add( QColor &left_var, const int &r, const int &g, const int &b, const int &a ) {
	left_var = QColor( left_var.red( ) + r, left_var.green( ) + g, left_var.blue( ) + b, left_var.alpha( ) + a );
	return true;
}
bool ImageTools::colorOperation::div( QColor &left_var, const int &r, const int &g, const int &b, const int &a ) {
	left_var = QColor( r ? left_var.red( ) / r : 0, g ? left_var.green( ) / g : 0, b ? left_var.blue( ) / b : 0, a ? left_var.alpha( ) / a : 0 );
	return true;
}
bool ImageTools::colorOperation::mul( QColor &left_var, const int &r, const int &g, const int &b, const int &a ) {
	left_var = QColor( r ? left_var.red( ) * r : 0, g ? left_var.green( ) * g : 0, b ? left_var.blue( ) * b : 0, a ? left_var.alpha( ) * a : 0 );
	return true;
}
bool ImageTools::imageOperation::mod( QImage &left_var, const QImage &right_var ) {
	int leftWidth = left_var.width( );
	int leftHeight = left_var.height( );
	int rightWidth = left_var.width( );
	int rightHeight = left_var.height( );
	if( leftWidth > rightWidth )
		leftWidth = rightWidth;
	if( leftHeight > rightHeight )
		leftHeight = rightHeight;

	size_t widthIndex;
	size_t heightIndex;
	QColor copyColor;
	for( widthIndex = 0; widthIndex < leftWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < leftHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::mod( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::sub( QImage &left_var, const QImage &right_var ) {
	int leftWidth = left_var.width( );
	int leftHeight = left_var.height( );
	int rightWidth = left_var.width( );
	int rightHeight = left_var.height( );
	if( leftWidth > rightWidth )
		leftWidth = rightWidth;
	if( leftHeight > rightHeight )
		leftHeight = rightHeight;
	
	size_t widthIndex;
	size_t heightIndex;
	QColor copyColor;
	for( widthIndex = 0; widthIndex < leftWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < leftHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::sub( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::add( QImage &left_var, const QImage &right_var ) {
	int leftWidth = left_var.width( );
	int leftHeight = left_var.height( );
	int rightWidth = left_var.width( );
	int rightHeight = left_var.height( );
	if( leftWidth > rightWidth )
		leftWidth = rightWidth;
	if( leftHeight > rightHeight )
		leftHeight = rightHeight;
	
	size_t widthIndex;
	size_t heightIndex;
	QColor copyColor;
	for( widthIndex = 0; widthIndex < leftWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < leftHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::add( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::div( QImage &left_var, const QImage &right_var ) {
	int leftWidth = left_var.width( );
	int leftHeight = left_var.height( );
	int rightWidth = left_var.width( );
	int rightHeight = left_var.height( );
	if( leftWidth > rightWidth )
		leftWidth = rightWidth;
	if( leftHeight > rightHeight )
		leftHeight = rightHeight;

	size_t widthIndex;
	size_t heightIndex;
	QColor copyColor;
	for( widthIndex = 0; widthIndex < leftWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < leftHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::div( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::mul( QImage &left_var, const QImage &right_var ) {
	int leftWidth = left_var.width( );
	int leftHeight = left_var.height( );
	int rightWidth = left_var.width( );
	int rightHeight = left_var.height( );
	if( leftWidth > rightWidth )
		leftWidth = rightWidth;
	if( leftHeight > rightHeight )
		leftHeight = rightHeight;
	
	size_t widthIndex;
	size_t heightIndex;
	QColor copyColor;
	for( widthIndex = 0; widthIndex < leftWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < leftHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::mul( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::mod( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height ) {
	size_t widthIndex = left_var.width( );
	size_t heightIndex = left_var.height( );
	size_t rightWidth = left_var.width( );
	size_t rightHeight = left_var.height( );

	if( rightWidth > widthIndex )
		rightWidth = widthIndex;
	if( rightHeight > heightIndex )
		rightHeight = heightIndex;

	if( rightWidth > width )
		rightWidth = width;
	if( rightHeight > height )
		rightHeight = height;

	QColor copyColor;
	for( widthIndex = 0; widthIndex < rightWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < rightHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::mod( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::sub( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height ) {
	size_t widthIndex = left_var.width( );
	size_t heightIndex = left_var.height( );
	size_t rightWidth = left_var.width( );
	size_t rightHeight = left_var.height( );

	if( rightWidth > widthIndex )
		rightWidth = widthIndex;
	if( rightHeight > heightIndex )
		rightHeight = heightIndex;

	if( rightWidth > width )
		rightWidth = width;
	if( rightHeight > height )
		rightHeight = height;

	QColor copyColor;
	for( widthIndex = 0; widthIndex < rightWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < rightHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::sub( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::add( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height ) {
	size_t widthIndex = left_var.width( );
	size_t heightIndex = left_var.height( );
	size_t rightWidth = left_var.width( );
	size_t rightHeight = left_var.height( );

	if( rightWidth > widthIndex )
		rightWidth = widthIndex;
	if( rightHeight > heightIndex )
		rightHeight = heightIndex;

	if( rightWidth > width )
		rightWidth = width;
	if( rightHeight > height )
		rightHeight = height;

	QColor copyColor;
	for( widthIndex = 0; widthIndex < rightWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < rightHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::add( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::div( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height ) {
	size_t widthIndex = left_var.width( );
	size_t heightIndex = left_var.height( );
	size_t rightWidth = left_var.width( );
	size_t rightHeight = left_var.height( );

	if( rightWidth > widthIndex )
		rightWidth = widthIndex;
	if( rightHeight > heightIndex )
		rightHeight = heightIndex;

	if( rightWidth > width )
		rightWidth = width;
	if( rightHeight > height )
		rightHeight = height;

	QColor copyColor;
	for( widthIndex = 0; widthIndex < rightWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < rightHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::div( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
bool ImageTools::imageOperation::mul( QImage &left_var, const QImage &right_var, const size_t &width, const size_t &height ) {
	size_t widthIndex = left_var.width( );
	size_t heightIndex = left_var.height( );
	size_t rightWidth = left_var.width( );
	size_t rightHeight = left_var.height( );

	if( rightWidth > widthIndex )
		rightWidth = widthIndex;
	if( rightHeight > heightIndex )
		rightHeight = heightIndex;

	if( rightWidth > width )
		rightWidth = width;
	if( rightHeight > height )
		rightHeight = height;

	QColor copyColor;
	for( widthIndex = 0; widthIndex < rightWidth; ++widthIndex )
		for( heightIndex = 0; heightIndex < rightHeight; ++heightIndex ) {
			copyColor = left_var.pixelColor( widthIndex, heightIndex );
			colorOperation::mul( copyColor, right_var.pixelColor( widthIndex, heightIndex ) );
			left_var.setPixelColor( widthIndex, heightIndex, copyColor );
		}
	return true;
}
