#include "./I_Conver.h"

bool I_Conver::fillInt( const QString *string, void *fill_target, const type_info &target_type_info ) {
	bool is_ok = false;
	if( stringFillToNumTypeVar< int64_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< uint64_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< int32_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< uint32_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< int16_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< uint16_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< int8_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	if( stringFillToNumTypeVar< uint8_t >( string, fill_target, target_type_info, &is_ok ) )
		return true;
	return false;
}
