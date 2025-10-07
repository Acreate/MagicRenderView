#include "uIntToString.h"

#include "../../../generate/varGenerate.h"

bool UIntToString::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [&right_type_info, right, this] ( QString *ptr ) {
		auto run_function = [&ptr] ( const auto *uintVar ) {
			*ptr = QString::number( *uintVar );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this] ( std::string *ptr ) {
		auto run_function = [&ptr] ( const auto *uintVar ) {
			*ptr = QString::number( *uintVar ).toStdString( );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this] ( std::wstring *ptr ) {
		auto run_function = [&ptr] ( const auto *uintVar ) {
			*ptr = QString::number( *uintVar ).toStdWString( );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool UIntToString::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	double doubleVar = 0;
	auto qstringFunction = [&right_type_info,&doubleVar, right, this] ( QString *ptr ) {

		bool isOk = false;
		doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, &doubleVar] ( const auto *uintVar ) {
			doubleVar += *uintVar;
			*ptr = QString::number( doubleVar );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, &doubleVar, right, this] ( std::string *ptr ) {

		bool isOk = false;
		doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, &doubleVar] ( const auto *uintVar ) {
			doubleVar += *uintVar;
			*ptr = QString::number( doubleVar ).toStdString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, &doubleVar, right, this] ( std::wstring *ptr ) {

		bool isOk = false;
		doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, &doubleVar] ( const auto *uintVar ) {
			doubleVar += *uintVar;
			*ptr = QString::number( doubleVar ).toStdWString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [&right_type_info, right, this] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, &doubleVar] ( const auto *uintVar ) {
			doubleVar -= *uintVar;
			*ptr = QString::number( doubleVar );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, &doubleVar] ( const auto *uintVar ) {
			doubleVar -= *uintVar;
			*ptr = QString::number( doubleVar ).toStdString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			doubleVar -= *uintVar;
			*ptr = QString::number( doubleVar ).toStdWString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [&right_type_info, right, this] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			doubleVar *= *uintVar;
			*ptr = QString::number( doubleVar );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			doubleVar *= *uintVar;
			*ptr = QString::number( doubleVar ).toStdString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			doubleVar *= *uintVar;
			*ptr = QString::number( doubleVar ).toStdWString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [&right_type_info, right, this] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			if( *uintVar != 0 )
				doubleVar /= *uintVar;
			*ptr = QString::number( doubleVar );
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			if( *uintVar != 0 )
				doubleVar /= *uintVar;
			*ptr = QString::number( doubleVar ).toStdString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar] ( const auto *uintVar ) {
			if( *uintVar != 0 )
				doubleVar /= *uintVar;
			*ptr = QString::number( doubleVar ).toStdWString( );
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar == *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this, result_bool] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar == *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this, result_bool] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar == *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar >= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this, result_bool] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar >= *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this, result_bool] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar >= *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar > *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this, result_bool] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar > *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this, result_bool] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar > *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar <= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this, result_bool] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar <= *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this, result_bool] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar <= *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}
bool UIntToString::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar < *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [&right_type_info, right, this, result_bool] ( std::string *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar < *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [&right_type_info, right, this, result_bool] ( std::wstring *ptr ) {

		bool isOk = false;
		double doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr,  &doubleVar, result_bool] ( const auto *uintVar ) {
			*result_bool = doubleVar < *uintVar;
			return true;
		};

		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;
	return false;
}

bool UIntToString::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isString( left_type_info ) && I_Type::isUInt( right_type_info ) )
		return true;
	return false;
}
