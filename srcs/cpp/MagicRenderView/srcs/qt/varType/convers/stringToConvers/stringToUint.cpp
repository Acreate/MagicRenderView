#include "stringToUint.h"

#include "../../../generate/varGenerate.h"

bool StringToUint::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [ &left_type_info, left] ( const QString *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = ptr->toDouble( &isOK );
			if( isOK )
				fillTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [ &left_type_info, left] ( const std::string *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdString( *ptr ).toDouble( &isOK );
			if( isOK )
				fillTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [ &left_type_info, left] ( const std::wstring *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
			if( isOK )
				fillTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool StringToUint::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [ &left_type_info, left] ( const QString *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = ptr->toDouble( &isOK );
			if( isOK )
				addTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [ &left_type_info, left] ( const std::string *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdString( *ptr ).toDouble( &isOK );
			if( isOK )
				addTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [ &left_type_info, left] ( const std::wstring *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
			if( isOK )
				addTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool StringToUint::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [ &left_type_info, left] ( const QString *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = ptr->toDouble( &isOK );
			if( isOK )
				subTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [ &left_type_info, left] ( const std::string *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdString( *ptr ).toDouble( &isOK );
			if( isOK )
				subTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [ &left_type_info, left] ( const std::wstring *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
			if( isOK )
				subTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool StringToUint::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [ &left_type_info, left] ( const QString *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = ptr->toDouble( &isOK );
			if( isOK )
				mulTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [ &left_type_info, left] ( const std::string *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdString( *ptr ).toDouble( &isOK );
			if( isOK )
				mulTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [ &left_type_info, left] ( const std::wstring *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
			if( isOK )
				mulTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool StringToUint::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto qstringFunction = [ &left_type_info, left] ( const QString *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = ptr->toDouble( &isOK );
			if( isOK )
				divTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( left_type_info, left, qstringFunction ) )
		return true;
	auto stdstringFunction = [ &left_type_info, left] ( const std::string *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdString( *ptr ).toDouble( &isOK );
			if( isOK )
				divTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( left_type_info, left, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [ &left_type_info, left] ( const std::wstring *ptr ) {
		auto run_function = [&ptr] ( auto *uintVar ) {
			bool isOK = false;
			double newVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
			if( isOK )
				divTargetFcuntion( *uintVar, newVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, run_function )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( left_type_info, left, stdwstringFunction ) )
		return true;

	return false;
}
bool StringToUint::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [&right_type_info, right, this, result_bool] ( QString *ptr ) {

		bool isOk = false;
		double doubleVar = ptr->toDouble( &isOk );
		if( isOk == false )
			return false;

		auto run_function = [&ptr, doubleVar, result_bool] ( const auto *uintVar ) {
			equThanTargetFcuntion( *result_bool, doubleVar, *uintVar );
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

		auto run_function = [&ptr, doubleVar, result_bool] ( const auto *uintVar ) {
			equThanTargetFcuntion( *result_bool, doubleVar, *uintVar );
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

		auto run_function = [&ptr, doubleVar, result_bool] ( const auto *uintVar ) {
			equThanTargetFcuntion( *result_bool, doubleVar, *uintVar );
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
bool StringToUint::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [this,result_bool, &left_type_info, left] ( const QString *ptr ) {
		bool isOK = false;
		auto doubleVar = ptr->toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( right_type_info, right, qstringFunction ) )
		return true;

	auto stdstringFunction = [this, result_bool, &left_type_info, left] ( const std::string *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( right_type_info, right, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [result_bool, &left_type_info, left] ( const std::wstring *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( right_type_info, right, stdwstringFunction ) )
		return true;
	return false;
}
bool StringToUint::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [result_bool, &left_type_info, left] ( const QString *ptr ) {
		bool isOK = false;
		auto doubleVar = ptr->toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( right_type_info, right, qstringFunction ) )
		return true;

	auto stdstringFunction = [result_bool, &left_type_info, left] ( const std::string *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( right_type_info, right, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [result_bool, &left_type_info, left] ( const std::wstring *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			greaterThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( right_type_info, right, stdwstringFunction ) )
		return true;
	return false;
}
bool StringToUint::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [result_bool, &left_type_info, left] ( const QString *ptr ) {
		bool isOK = false;
		auto doubleVar = ptr->toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( right_type_info, right, qstringFunction ) )
		return true;

	auto stdstringFunction = [result_bool, &left_type_info, left] ( const std::string *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( right_type_info, right, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [result_bool, &left_type_info, left] ( const std::wstring *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessOrEquThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( right_type_info, right, stdwstringFunction ) )
		return true;
	return false;
}
bool StringToUint::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto qstringFunction = [result_bool, &left_type_info, left] ( const QString *ptr ) {
		bool isOK = false;
		auto doubleVar = ptr->toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< QString >( right_type_info, right, qstringFunction ) )
		return true;

	auto stdstringFunction = [result_bool, &left_type_info, left] ( const std::string *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::string >( right_type_info, right, stdstringFunction ) )
		return true;
	auto stdwstringFunction = [result_bool, &left_type_info, left] ( const std::wstring *ptr ) {
		bool isOK = false;
		auto doubleVar = QString::fromStdWString( *ptr ).toDouble( &isOK );
		if( isOK == false )
			return false;
		auto uintCall = [ result_bool, doubleVar] ( auto *uintPtr ) {
			lessThanTargetFcuntion( *result_bool, *uintPtr, doubleVar );
			return true;
		};
		if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, uintCall )
			|| I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, uintCall ) )
			return true;
		return true;
	};
	if( I_Conver::rightConverPtrTypeToTargetType< std::wstring >( right_type_info, right, stdwstringFunction ) )
		return true;
	return false;
}

bool StringToUint::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {

	if( I_Type::isUInt( left_type_info ) && I_Type::isString( right_type_info ) )
		return true;
	return false;
}
