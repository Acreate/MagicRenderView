#include "uIntToUInt.h"

#include "../../../generate/varGenerate.h"

bool UIntToUInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
	if( I_Conver::leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function ) ||
		I_Conver::leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool UIntToUInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isUInt( left_type_info ) && I_Type::isUInt( right_type_info ) )
		return true;
	return false;
}
