/* 
 * File:   IteratorWrapper.hpp
 * 
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_ITERATORWRAPPER_HPP
#define HTD_HTD_ITERATORWRAPPER_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Implementation of a wrapper for iterators of mutable collections.
     */
    template <typename Iter, typename T = typename Iter::value_type>
    class IteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public htd::IteratorBase<T>
    {
            public:
            /**
             *  Constructor for an iterator wrapper.
             *
             *  @param[in] baseIterator The underlying iterator which shall be wrapped.
             */
            IteratorWrapper(Iter baseIterator) : baseIterator_(baseIterator)
            {

            }

            /**
             *  Copy constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            IteratorWrapper(const IteratorWrapper & original) : baseIterator_(original.baseIterator_)
            {

            }

            /**
             *  Move constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            IteratorWrapper(IteratorWrapper && original) : baseIterator_(std::move(original.baseIterator_))
            {

            }

            virtual ~IteratorWrapper()
            {

            }

            /**
             *  Copy assignment operator for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            IteratorWrapper & operator=(const IteratorWrapper & original)
            {
                baseIterator_ = original.baseIterator_;

                return *this;
            }

            IteratorWrapper & operator++(void) override
            {
                ++baseIterator_;

                return *this;
            }

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            IteratorWrapper operator++(int)
            {
                IteratorWrapper ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const htd::IteratorBase<T> & rhs) const override
            {
                return baseIterator_ == static_cast<const IteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const IteratorWrapper & rhs) const
            {
                return baseIterator_ == rhs.baseIterator_;
            }

            bool operator!=(const htd::IteratorBase<T> & rhs) const override
            {
                return baseIterator_ != static_cast<const IteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const IteratorWrapper & rhs) const
            {
                return baseIterator_ != rhs.baseIterator_;
            }

            T * operator->(void) override
            {
                return &(*baseIterator_);
            }

            /**
             *  Dereference the iterator.
             *
             *  @return A pointer to the element at the current iterator position.
             */
            const T * operator->(void) const
            {
                return &(*baseIterator_);
            }

            T & operator*(void) override
            {
                return *baseIterator_;
            }

            /**
             *  Dereference the iterator.
             *
             *  @return A reference to the element at the current iterator position.
             */
            const T & operator*(void) const
            {
                return *baseIterator_;
            }

            IteratorWrapper * clone(void) const override
            {
                return new IteratorWrapper(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_ITERATORWRAPPER_HPP */

