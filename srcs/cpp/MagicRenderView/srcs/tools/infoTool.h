#ifndef INFOTOOL_H_H_HEAD__FILE__
#define INFOTOOL_H_H_HEAD__FILE__

#include <QImage>
#include <QColor>
#include <QBuffer>
#include <QDateTime>
#include <qstring.h>

class VarDirector;
namespace infoTool {
	bool toString( const QColor *conver_color_ptr, QString &result_string );
	inline bool toString( const QColor &conver_color_ref, QString &result_string ) {
		return toString( &conver_color_ref, result_string );
	}
	bool toString( const VarDirector *var_director_ptr, void const *conver_var_ptr, QString &result_string );
	bool fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result );
	bool fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count );
	inline bool fillObjTarget( uint64_t &result_count, const void *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( uint8_t * ) ptr, ptr_size, result );
	}
	template< typename TSourceType >
	bool fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
		return fillVectorTarget( ( const uint8_t * ) ptr, sizeof( TSourceType ) / sizeof( uint8_t ), result );
	}
	template< typename TSourceType >
	bool fillTypeVectorAtVar( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, TSourceType *target_var_ptr ) {
		return fillObjTarget( result_count, source_ptr, source_count, ( uint8_t * ) target_var_ptr, sizeof( TSourceType ) / sizeof( uint8_t ) );
	}
	template<>
	inline bool fillTypeVarAtVector< QString >( const void *ptr, std::vector< uint8_t > &result ) {
		QString *stringPtr = ( QString * ) ptr;
		std::vector< uint8_t > buff;
		auto local8Bit = stringPtr->toUtf8( );
		auto converVar = local8Bit.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		char *data = local8Bit.data( );
		if( fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QString >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QString *target_var_ptr ) {
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		*target_var_ptr = QString::fromUtf8( ( const char * ) offset, result_count );
		result_count = result_count + sizeTypeCount;
		return result_count;
	}

	template<>
	inline bool fillTypeVarAtVector< QChar >( const void *ptr, std::vector< uint8_t > &result ) {
		const QChar *stringPtr = ( const QChar * ) ptr;
		std::vector< uint8_t > buff;
		auto local8Bit = stringPtr->unicode( );
		auto converVar = sizeof( local8Bit );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		char *data = ( char * ) &local8Bit;
		if( fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QChar >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QChar *target_var_ptr ) {
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		auto unicodePtr = target_var_ptr->unicode( );
		if( fillTypeVectorAtVar( result_count, offset, mod, &unicodePtr ) == false )
			return false;
		*target_var_ptr = QChar::fromUcs2( unicodePtr );
		result_count = result_count + sizeTypeCount;
		return result_count;
	}
	template<>
	inline bool fillTypeVarAtVector< QImage >( const void *ptr, std::vector< uint8_t > &result ) {
		QImage *imagePtr = ( QImage * ) ptr;
		std::vector< uint8_t > buff;

		QByteArray ba;
		QBuffer buffer( &ba );
		buffer.open( QIODevice::WriteOnly );
		imagePtr->save( &buffer, "PNG" );

		auto data = ba.constData( );
		auto converVar = ba.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		if( fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QImage >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QImage *target_var_ptr ) {
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		QByteArray ba( ( const char * ) offset, result_count );
		target_var_ptr->loadFromData( ba );
		result_count = result_count + sizeTypeCount;
		return result_count;
	}

	template<>
	inline bool fillTypeVarAtVector< QColor >( const void *ptr, std::vector< uint8_t > &result ) {
		QColor *colorPtr = ( QColor * ) ptr;
		int r, g, b, a;
		colorPtr->getRgb( &r, &g, &b, &a );
		std::vector< uint8_t > buff;
		std::vector< uint8_t > colorBuff;
		if( fillTypeVarAtVector< uint64_t >( &r, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &g, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &b, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &a, buff ) == false )
			return false;
		colorBuff.append_range( buff );

		auto converVar = colorBuff.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		auto *data = colorBuff.data( );
		if( fillVectorTarget( data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QColor >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QColor *target_var_ptr ) {
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		sizeTypeCount = sizeof( int );
		if( mod < ( sizeTypeCount * 4 ) )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		int r, g, b, a;
		r = *( int * ) offset;
		offset = source_ptr + sizeTypeCount;
		g = *( int * ) offset;
		offset = source_ptr + sizeTypeCount;
		b = *( int * ) offset;
		offset = source_ptr + sizeTypeCount;
		a = *( int * ) offset;
		offset = source_ptr + sizeTypeCount;
		target_var_ptr->setRgba( qRgba( r, g, b, a ) );
		result_count = offset - source_ptr;
		return result_count;
	}
}

#endif // INFOTOOL_H_H_HEAD__FILE__
