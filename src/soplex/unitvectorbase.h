/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*  Copyright 1996-2022 Zuse Institute Berlin                                */
/*                                                                           */
/*  Licensed under the Apache License, Version 2.0 (the "License");          */
/*  you may not use this file except in compliance with the License.         */
/*  You may obtain a copy of the License at                                  */
/*                                                                           */
/*      http://www.apache.org/licenses/LICENSE-2.0                           */
/*                                                                           */
/*  Unless required by applicable law or agreed to in writing, software      */
/*  distributed under the License is distributed on an "AS IS" BASIS,        */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*  See the License for the specific language governing permissions and      */
/*  limitations under the License.                                           */
/*                                                                           */
/*  You should have received a copy of the Apache-2.0 license                */
/*  along with SoPlex; see the file LICENSE. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file  unitvector.h
 * @brief Sparse vector \f$e_i\f$.
 */

#ifndef _UNITVECTORBASE_H_
#define _UNITVECTORBASE_H_

#include <assert.h>
#include "soplex/spxdefines.h"
#include "soplex/svectorbase.h"

namespace soplex
{


/**@brief   Sparse vector \f$e_i\f$.
   @ingroup Algebra

   A UnitVectorBase is an SVectorBase that can take only one nonzero value with
   value 1 but arbitrary index.

   \todo Several SVectorBase modification methods are still accessible for UnitVector.
   They might be used to change the vector.

   \todo UnitVectorBase memory management must be changed when SVectorBase is redesigned.
*/

template < class R >
class UnitVectorBase : public SVectorBase<R>
{
private:

   //------------------------------------
   /**@name Data */
   ///@{
   typename SVectorBase<R>::Element themem;  ///< memory for sparse vector entry
   ///@}

   using SVectorBase<R>::mem;

   using SVectorBase<R>::size;

   using SVectorBase<R>::max;

public:

   //------------------------------------
   /**@name Access */
   ///@{
   /// returns value = 1
   /**\pre \c n must be 0.
    */
   /* ARGSUSED n */
   R value(int n) const
   {
      assert(n == 0);
      return 1;
   }
   ///@}

   //------------------------------------
   /**@name Constructors / destructors */
   ///@{
   /// construct \c i 'th unit vector.
   explicit
   UnitVectorBase(int i = 0)
      : SVectorBase<R>(1, &themem)
   {
      // coverity[callee_ptr_arith]
      SVectorBase<R>::add(i, 1.0);

      assert(isConsistent());
   }
   ///  copy constructor
   UnitVectorBase(const UnitVectorBase<R>& rhs)
      : SVectorBase<R>(1, &themem)
   {
      themem = rhs.themem;
      this->set_size(1);

      assert(isConsistent());
   }
   /// assignment
   UnitVectorBase<R>& operator=(const UnitVectorBase<R>& rhs)
   {
      if(this != &rhs)
      {
         themem = rhs.themem;
         this->set_size(1);

         assert(isConsistent());
      }

      return *this;
   }
   /// destructor
   ~UnitVectorBase()
   {}
   ///@}

   //------------------------------------
   /**@name Miscellaneous */
   ///@{
   /// consistency check
   bool isConsistent() const
   {
#ifdef ENABLE_CONSISTENCY_CHECKS

      if(mem() != &themem)
         return SPX_MSG_INCONSISTENT("UnitVectorBase");

      if(size() != 1)
         return SPX_MSG_INCONSISTENT("UnitVectorBase");

      if(max() != 1)
         return SPX_MSG_INCONSISTENT("UnitVectorBase");

      return SVectorBase<R>::isConsistent();
#else
      return true;
#endif
   }
   ///@}
};


} // namespace soplex
#endif // _UNITVECTORBASE_H_
