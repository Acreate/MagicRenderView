#ifndef VARDIRECTORTOOLS_H_H_HEAD__FILE__
#define VARDIRECTORTOOLS_H_H_HEAD__FILE__

class QString;
class VarDirector;
namespace VarDirectorTools {
	bool isTrue( const VarDirector *varDirectorPtr, const void *var_ptr );
	bool toString( const VarDirector *var_director_ptr, void const *conver_var_ptr, QString &result_string );
}

#endif // VARDIRECTORTOOLS_H_H_HEAD__FILE__
