#include "uIntToInt.h"

#include "../../../generate/varGenerate.h"

bool UIntToInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [&ptr] ( const auto *uintVar ) {
			*ptr = *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr += *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr -= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr *= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			if( *uintVar != 0 )
				*ptr /= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr == *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr >= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr > *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr <= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr < *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function )
			|| I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	if( I_Conver::leftConverPtrTypeToTargetType< int8_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int16_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int32_t >( left_type_info, left, function )
		|| I_Conver::leftConverPtrTypeToTargetType< int64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isInt( left_type_info ) && I_Type::isUInt( right_type_info ) )
		return true;
	return false;
}
