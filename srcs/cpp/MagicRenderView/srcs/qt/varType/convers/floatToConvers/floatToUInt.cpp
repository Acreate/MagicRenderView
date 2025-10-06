#include "floatToUInt.h"

#include "../../../generate/varGenerate.h"

bool FloatToUInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr = *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr += *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr -= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr *= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( const auto *uintVar ) {
			if( *uintVar != 0 )
				*ptr /= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr == *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr >= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr > *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr <= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}
bool FloatToUInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr < *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< float_t >( right_type_info, right, run_function ) || I_Conver::rightConverPtrTypeToTargetType< double_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	if( leftConverPtrTypeToTargetType< uint8_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint16_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint32_t >( left_type_info, left, function )
		|| leftConverPtrTypeToTargetType< uint64_t >( left_type_info, left, function ) )
		return true;

	return false;
}

bool FloatToUInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isUInt( left_type_info ) && I_Type::isFloat( right_type_info ) )
		return true;
	return false;
}
