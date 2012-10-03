
namespace CGAL {

/*!
\ingroup kernel_predef

A typedef to a kernel which has the following properties: 

<UL> 
<LI>It uses %Cartesian representation. 
<LI>It supports constructions of points from `double` %Cartesian 
coordinates. 
<LI>It provides both exact geometric predicates and exact geometric 
constructions. 
<LI>Its `FT` nested type supports the square root operation `sqrt()`. 
</UL> 

Note that it requires CORE or LEDA installed. 

\models ::Kernel 

\sa `CGAL::Exact_predicates_exact_constructions_kernel` 
\sa `CGAL::Exact_predicates_inexact_constructions_kernel` 
\sa `CGAL::Cartesian` 

*/

class Exact_predicates_exact_constructions_kernel_with_sqrt {
public:

/// @}

}; /* end Exact_predicates_exact_constructions_kernel_with_sqrt */
} /* end namespace CGAL */
