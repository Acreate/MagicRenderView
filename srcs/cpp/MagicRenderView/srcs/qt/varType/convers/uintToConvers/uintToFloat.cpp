#include "uintToFloat.h"

#include "../../../generate/varGenerate.h"
bool UintToFloat::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr = *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr += *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr -= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( auto *uintVar ) {
			*ptr *= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto function = [&right_type_info, right, this] ( auto *ptr ) {
		auto run_function = [ptr] ( const auto *uintVar ) {
			if( *uintVar != 0 )
				*ptr /= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr == *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr >= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr > *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr <= *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;

		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto function = [&right_type_info, right, this, result_bool] ( auto *ptr ) {
		auto run_function = [ptr, result_bool] ( auto *uintVar ) {
			*result_bool = *ptr < *uintVar;
			return true;
		};
		if( I_Conver::rightConverPtrTypeToTargetType< uint8_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint16_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint32_t >( right_type_info, right, run_function ) )
			return true;
		if( I_Conver::rightConverPtrTypeToTargetType< uint64_t >( right_type_info, right, run_function ) )
			return true;
		return false;
	};
	bool runFlag = leftConverPtrTypeToTargetType< float_t >( left_type_info, left, function );
	if( runFlag )
		return true;
	runFlag = leftConverPtrTypeToTargetType< double_t >( left_type_info, left, function );
	if( runFlag )
		return true;

	return false;
}
bool UintToFloat::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isFloat( left_type_info ) && I_Type::isUInt( right_type_info ) )
		return true;
	return false;
}
