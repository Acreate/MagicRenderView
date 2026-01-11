#ifndef BASEOPERATIONTOOLS_H_H_HEAD__FILE__
#define BASEOPERATIONTOOLS_H_H_HEAD__FILE__

namespace BaseOperationTools {
	template< typename TLModType, typename TRModType >
	bool mod( TLModType &left_var, const TRModType &right_var ) {
		while( left_var > right_var )
			left_var -= right_var;
		return true;
	}
};

#endif // BASEOPERATIONTOOLS_H_H_HEAD__FILE__
