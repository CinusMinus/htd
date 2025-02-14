/* 
 * File:   ConstPointerIteratorWrapper.hpp
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

#ifndef HTD_HTD_CONSTPOINTERITERATORWRAPPER_HPP
#define HTD_HTD_CONSTPOINTERITERATORWRAPPER_HPP

#include <htd/Globals.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Implementation of a wrapper for iterators of immutable collections of pointers.
     */
    template <typename Iter, typename T>
    class ConstPointerIteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public htd::ConstIteratorBase<T>
    {
        public:
            /**
             *  Constructor for a wrapper of an iterator over a collection of pointers.
             *
             *  @param[in] baseIterator The underlying iterator which shall be wrapped.
             */
            ConstPointerIteratorWrapper(Iter baseIterator) noexcept : baseIterator_(baseIterator)
            {

            }

            /**
             *  Copy constructor for a wrapper of an iterator over a collection of pointers.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstPointerIteratorWrapper(const ConstPointerIteratorWrapper & original) noexcept : baseIterator_(original.baseIterator_)
            {

            }

            /**
             *  Move constructor for a wrapper of an iterator over a collection of pointers.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstPointerIteratorWrapper(ConstPointerIteratorWrapper && original) noexcept : baseIterator_(std::move(original.baseIterator_))
            {

            }

            virtual ~ConstPointerIteratorWrapper()
            {

            }

            /**
             *  Copy assignment operator for a wrapper of an iterator over a collection of pointers.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstPointerIteratorWrapper & operator=(ConstPointerIteratorWrapper & original)
            {
                baseIterator_ = original.baseIterator_;

                return *this;
            }

            ConstPointerIteratorWrapper & operator++(void) noexcept override
            {
                ++baseIterator_;

                return *this;
            }

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            ConstPointerIteratorWrapper operator++(int)
            {
                ConstPointerIteratorWrapper ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const htd::ConstIteratorBase<T> & rhs) const noexcept override
            {
                return baseIterator_ == static_cast<const ConstPointerIteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const ConstPointerIteratorWrapper & rhs) const
            {
                return baseIterator_ == rhs.baseIterator_;
            }

            bool operator!=(const htd::ConstIteratorBase<T> & rhs) const noexcept override
            {
                return baseIterator_ != static_cast<const ConstPointerIteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const ConstPointerIteratorWrapper & rhs) const
            {
                return baseIterator_ != rhs.baseIterator_;
            }

            const T * operator->(void) const override
            {
                return *baseIterator_;
            }

            const T & operator*(void) const override
            {
                return *(*baseIterator_);
            }

            ConstPointerIteratorWrapper * clone(void) const noexcept override
            {
                return new ConstPointerIteratorWrapper(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_CONSTPOINTERITERATORWRAPPER_HPP */
