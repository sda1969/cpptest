/*
 * templatetest.h
 *
 *  Created on: 17 окт. 2018 г.
 *      Author: user
 */

#ifndef TEMPLATETEST_H_
#define TEMPLATETEST_H_

namespace templatetest {

template <class T, T v>
struct integral_constant {
  static constexpr T value = v;
  typedef T value_type;
  typedef integral_constant<T,v> type;
  constexpr  operator T() const noexcept { return v; }
  constexpr T operator()() const noexcept { return v; }
};


void templatetest_run();

}


#endif /* TEMPLATETEST_H_ */
