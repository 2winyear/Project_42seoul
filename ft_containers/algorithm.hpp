#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

/* equal */
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1,
           InputIterator1 last1,
           InputIterator2 first2) {
  for ( ; first1 != last1 ; first1++, first2++) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1,
           InputIterator1 last1,
           InputIterator2 first2,
           BinaryPredicate pred) { // BinaryPredicate pred가 뭐하는거지 문자열 전체를 입력받던대
  for ( ; first1 != last1 ; first1++, first2++) {
    if (!pred(*first1, *first2)) {
      return false;
    }
    return true;
  }
}

/* lexicographical_compare */
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             InputIterator2 last2) {
  for ( ; first2 != last2 ; first1++, first2++) {
    if (first1 == last1 || *first1 < *first2) { // first1이 작은 경우도 true?
      return true;
    }
    if (*first1 > *first2) {
      return false;
    }
  }
  return false;
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             InputIterator2 last2,
                             Compare comp) {
  for ( ; first2 != last2 ; first1++, first2++) {
    if (first1 == last1 || comp(*first1, *first2)) {
      return true;
    }
    if (comp(*first2, *first1)) { // !comp(*first1, *first2)랑 같은건가?
      return false;
    }
  }
  return false;
}

} // namespace ft

#endif