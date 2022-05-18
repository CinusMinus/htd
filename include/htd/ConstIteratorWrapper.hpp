/* 
 * File:   ConstIteratorWrapper.hpp
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

#ifndef HTD_HTD_CONSTITERATORWRAPPER_HPP
#define HTD_HTD_CONSTITERATORWRAPPER_HPP

#include <htd/Globals.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Implementation of a wrapper for iterators of immutable collections.
     */
    template <typename Iter, typename T = typename Iter::value_type>
    class ConstIteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public htd::ConstIteratorBase<T>
    {
        public:
            /**
             *  Constructor for an iterator wrapper.
             *
             *  @param[in] baseIterator The underlying iterator which shall be wrapped.
             */
            ConstIteratorWrapper(Iter baseIterator) noexcept : baseIterator_(baseIterator)
            {

            }

            /**
             *  Copy constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper(const ConstIteratorWrapper & original) noexcept : baseIterator_(original.baseIterator_)
            {

            }

            /**
             *  Move constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper(ConstIteratorWrapper && original) noexcept : baseIterator_(std::move(original.baseIterator_))
            {

            }

            virtual ~ConstIteratorWrapper()
            {

            }

            /**
             *  Copy assignment operator for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper & operator=(ConstIteratorWrapper & original) noexcept
            {
                baseIterator_ = original.baseIterator_;

                return *this;
            }

            /**
             *  Move assignment operator for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper & operator=(ConstIteratorWrapper && original) noexcept
            {
                baseIterator_ = std::move(original.baseIterator_);

                return *this;
            }

            ConstIteratorWrapper & operator++(void) noexcept override
            {
                ++baseIterator_;

                return *this;
            }

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            ConstIteratorWrapper operator++(int) noexcept
            {
                ConstIteratorWrapper ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const ConstIteratorBase<T> & rhs) const noexcept override
            {
                return baseIterator_ == static_cast<const ConstIteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const ConstIteratorWrapper & rhs) const noexcept
            {
                return baseIterator_ == rhs.baseIterator_;
            }

            bool operator!=(const ConstIteratorBase<T> & rhs) const noexcept override
            {
                return baseIterator_ != static_cast<const ConstIteratorWrapper *>(&rhs)->baseIterator_;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const ConstIteratorWrapper & rhs) const noexcept
            {
                return baseIterator_ != rhs.baseIterator_;
            }

            const T * operator->(void) const override
            {
                return &(*baseIterator_);
            }

            const T & operator*(void) const override
            {
                return *baseIterator_;
            }

            ConstIteratorWrapper<Iter, T> * clone(void) const noexcept override
            {
                return new ConstIteratorWrapper(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_CONSTITERATORWRAPPER_HPP */
