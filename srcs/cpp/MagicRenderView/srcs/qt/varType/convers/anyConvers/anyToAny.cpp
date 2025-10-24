#include "anyToAny.h"

#include "../../../appType/any.h"
bool AnyToAny::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto leftTypePtr = isType< Any >( left_type_info, left );
	if( leftTypePtr == nullptr )
		return false;
	auto rightTypePtr = isType< Any >( right_type_info, right );
	if( rightTypePtr == nullptr )
		return false;

	return true;
}
bool AnyToAny::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	auto &typeInfo = typeid( Any );
	if( left_type_info != typeInfo )
		return false;
	if( right_type_info != typeInfo )
		return false;

	return true;
}
