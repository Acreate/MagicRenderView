#include "IFunctionDeclaration.h"

#include "qt/tools/tools.h"

inline bool findPairt( const QChar *data_ptr, const qsizetype &data_count, const qsizetype &start_index, const QChar &find_target, const QChar &exit_target, qsizetype &result_index ) {
	// 嵌套计数
	size_t pairtCount = 0;
	for( result_index = start_index; result_index < data_count; ++result_index )
		if( data_ptr[ result_index ] == '\\' )
			++result_index;
		else if( data_ptr[ result_index ] == exit_target ) {
			if( pairtCount == 0 )
				return true;
			else
				--pairtCount;
		} else if( data_ptr[ result_index ] == find_target )
			++pairtCount;
		else if( data_ptr[ result_index ] == '\'' && !findPairt( data_ptr, data_count, result_index + 1, '\'', '\'', result_index ) )
			return false;
		else if( data_ptr[ result_index ] == '\"' && !findPairt( data_ptr, data_count, result_index + 1, '\"', '\"', result_index ) )
			return false;
	return false;
}

inline bool findParams( const QChar *data_ptr, const qsizetype &data_count, const qsizetype &start_index, qsizetype &result_index ) {
	for( result_index = start_index; result_index < data_count; ++result_index )
		if( data_ptr[ result_index ] == '\\' )
			++result_index;
		else if( data_ptr[ result_index ] == ',' )
			return true;
		else if( data_ptr[ result_index ] == '\'' && findPairt( data_ptr, data_count, result_index + 1, '\'', '\'', result_index ) )
			return false;
		else if( data_ptr[ result_index ] == '\"' && !findPairt( data_ptr, data_count, result_index + 1, '\"', '\"', result_index ) )
			return false;
	return false;
}

bool IFunctionDeclaration::init( const QString &function_declaration_name ) {
	isValid = true;
	functionDeclarationName = function_declaration_name;
	auto declData = function_declaration_name.data( );
	qsizetype declCount = function_declaration_name.length( );

	// 检查属性
	qsizetype index = 0;
	qsizetype end = 0;

	// 找到非空
	for( ; index < declCount; ++index )
		if( !declData[ index ].isSpace( ) )
			break;
	if( declData[ index ] == '[' && !findPairt( declData, declCount, index + 1, '[', ']', end ) ) {
		tools::debug::printError( "无法匹配的 []，将检查属性功能是否存在异常" );
		isValid = false;
		return false;
	} else {
		qint64 count = end - index;
		if( count ) {
			attribute = function_declaration_name.mid( index, count + 1 );
			index = end + 1;
			// 找到非空
			for( ; index < declCount; ++index )
				if( !declData[ index ].isSpace( ) )
					break;
		}
	}

	// 找到空
	for( end = index + 1; end < declCount; ++end )
		if( declData[ end ].isSpace( ) )
			break;
	returnType = function_declaration_name.mid( index, end - index );

	// 找到非空
	for( index = end + 1; index < declCount; ++index )
		if( !declData[ index ].isSpace( ) )
			break;

	// 找到 (
	for( end = index + 1; end < declCount; ++end )
		if( declData[ end ] == '(' )
			break;
	declarationName = function_declaration_name.mid( index, end - index );
	index = end + 1;
	if( !findPairt( declData, declCount, index + 1, '(', ')', end ) ) {
		tools::debug::printError( "无法匹配的 ( )，将检查属性功能是否存在异常" );
		isValid = false;
		return false;
	}
	qint64 n = end - index;
	if( n == 0 )
		return true; // 没有发现参数列表
	auto arg = function_declaration_name.mid( index, n );
	QChar *dataPtr = arg.data( );
	qint64 dataCount = arg.count( );
	index = 0;
	// 找到第一个非空字符
	for( ; index < dataCount; ++index )
		if( !dataPtr[ index ].isSpace( ) )
			break;
	if( index == dataCount )
		return true; // 参数串全字符位空白
	std_vector< QString > params;
	QString mid;
	while( findParams( dataPtr, dataCount, index, end ) ) {
		mid = arg.mid( index, end - index );
		params.emplace_back( mid );
		// 找到非空
		for( index = end + 2; index < declCount; ++index )
			if( !dataPtr[ index ].isSpace( ) )
				break;
	}
	if( index < dataCount ) {
		mid = arg.mid( index );
		params.emplace_back( mid );
	}

	for( auto &argParam : params ) {
		declData = argParam.data( );
		declCount = argParam.size( );
		// 找到空
		for( index = 0; index < declCount; ++index )
			if( declData[ index ].isSpace( ) )
				break;
		arg = argParam.mid( 0, index );
		// 找到非空
		for( ; index < declCount; ++index )
			if( !declData[ index ].isSpace( ) )
				break;
		mid = argParam.mid( index );
		std_pairt< QString, QString > *pairt = new std_pairt< QString, QString >( arg, mid );
		paramInfo.emplace_back( std_shared_ptr< std_pairt< QString, QString > >( pairt ) );
	}
	return true;
}
IFunctionDeclaration::IFunctionDeclaration( const QString &function_declaration_name, const std_function< void( ) > &call_function ) : callFcuntion( call_function ) {
	if( init( function_declaration_name ) )
		return;
}
