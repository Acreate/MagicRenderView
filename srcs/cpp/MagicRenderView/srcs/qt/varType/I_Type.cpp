#include "./I_Type.h"
bool operator==( const I_Type &lhs, const I_Type &rhs ) {
	QString leftName = lhs.typeInfo.name( );

	QString leftRawName = lhs.typeInfo.raw_name( );
	size_t leftHashCode = lhs.typeInfo.hash_code( );
	QString rightName = rhs.typeInfo.name( );
	QString rightRawName = rhs.typeInfo.raw_name( );
	size_t rightHashCode = rhs.typeInfo.hash_code( );

	bool nameComp = leftName == rightName;
	bool hash_codeComp = leftHashCode == rightHashCode;
	bool raw_nameComp = leftRawName == rightRawName;
	return nameComp && hash_codeComp && raw_nameComp;
}
I_Type::I_Type( type_info &type_info ) : typeInfo( type_info ) { }
I_Type::I_Type( const type_info &type_info ) : typeInfo( type_info ) { }
I_Type::~I_Type( ) { }
I_Type::I_Type( const I_Type &other ) : typeInfo( other.typeInfo ) { }
