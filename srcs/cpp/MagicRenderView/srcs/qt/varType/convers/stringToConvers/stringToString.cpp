#include "stringToString.h"
bool StringToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar] ( QString *string ) {
		*leftVar = *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar] ( std::string *string ) {
		*leftVar = QString::fromStdString( *string );
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar] ( std::wstring *string ) {
		*leftVar = QString::fromStdWString( *string );
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar] ( QString *string ) {
		*leftVar += *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar] ( std::string *string ) {
		*leftVar += QString::fromStdString( *string );
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar] ( std::wstring *string ) {
		*leftVar += QString::fromStdWString( *string );
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar] ( QString *string ) {
		qsizetype indexOf = leftVar->indexOf( *string );
		if( indexOf == -1 )
			return true;
		leftVar->remove( indexOf, string->length( ) );
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		qsizetype indexOf = leftVar->indexOf( buff );
		if( indexOf == -1 )
			return true;
		leftVar->remove( indexOf, string->length( ) );
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		qsizetype indexOf = leftVar->indexOf( buff );
		if( indexOf == -1 )
			return true;
		leftVar->remove( indexOf, string->length( ) );
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar] ( QString *string ) {

		QStringList stringListBuff;
		qsizetype count = leftVar->size( );
		auto data = leftVar->data( );
		for( qsizetype index = 0; index < count; ++index ) {
			stringListBuff.append( data[ index ] );
			stringListBuff.append( *string );
		}
		*leftVar = stringListBuff.join( "" );
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );

		QStringList stringListBuff;
		qsizetype count = leftVar->size( );
		auto data = leftVar->data( );
		for( qsizetype index = 0; index < count; ++index ) {
			stringListBuff.append( data[ index ] );
			stringListBuff.append( buff );
		}
		*leftVar = stringListBuff.join( "" );
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );

		QStringList stringListBuff;
		qsizetype count = leftVar->size( );
		auto data = leftVar->data( );
		for( qsizetype index = 0; index < count; ++index ) {
			stringListBuff.append( data[ index ] );
			stringListBuff.append( buff );
		}
		*leftVar = stringListBuff.join( "" );
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar] ( QString *string ) {
		*leftVar = leftVar->split( *string ).join( "" );
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*leftVar = leftVar->split( buff ).join( "" );
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*leftVar = leftVar->split( buff ).join( "" );
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar, result_bool] ( QString *string ) {
		*result_bool = *leftVar == *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar, result_bool] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*result_bool = *leftVar == buff;
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar, result_bool] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*result_bool = *leftVar == buff;
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar, result_bool] ( QString *string ) {
		*result_bool = *leftVar >= *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar, result_bool] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*result_bool = *leftVar >= buff;
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar, result_bool] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*result_bool = *leftVar >= buff;
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar, result_bool] ( QString *string ) {
		*result_bool = *leftVar > *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar, result_bool] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*result_bool = *leftVar > buff;
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar, result_bool] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*result_bool = *leftVar > buff;
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar, result_bool] ( QString *string ) {
		*result_bool = *leftVar <= *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar, result_bool] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*result_bool = *leftVar <= buff;
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar, result_bool] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*result_bool = *leftVar <= buff;
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToString::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto qstringCall = [leftVar, result_bool] ( QString *string ) {
		*result_bool = *leftVar < *string;
		return true;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, qstringCall );
	if( typeCallResult )
		return true;
	auto stdStringCall = [leftVar, result_bool] ( std::string *string ) {
		QString buff = QString::fromStdString( *string );
		*result_bool = *leftVar < buff;
		return true;
	};
	typeCallResult = typeCall< std::string >( right_type_info, right, stdStringCall );
	if( typeCallResult )
		return true;
	auto stdWStringCall = [leftVar, result_bool] ( std::wstring *string ) {
		QString buff = QString::fromStdWString( *string );
		*result_bool = *leftVar < buff;
		return true;
	};
	typeCallResult = typeCall< std::wstring >( right_type_info, right, stdWStringCall );
	if( typeCallResult )
		return true;
	return false;
}
