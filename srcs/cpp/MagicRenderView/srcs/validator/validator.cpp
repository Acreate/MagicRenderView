#include "validator.h"

Validator::Validator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent ) : QValidator( parent ), maxValue( max_value ), minValue( min_value ), binSystem( bin_system ) {
	auto maxValueLen = tr( "%1" ).arg( maxValue, 0, binSystem ).length( );
	auto minValueLen = tr( "%1" ).arg( minValue, 0, binSystem ).length( );
	if( maxValueLen > minValueLen )
		maxLen = maxValueLen;
	else
		maxLen = minValueLen;

}
Validator::~Validator( ) {
}
