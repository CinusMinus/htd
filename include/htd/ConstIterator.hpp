/* 
 * File:   ConstIterator.hpp
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

#ifndef HTD_HTD_CONSTITERATOR_HPP
#define HTD_HTD_CONSTITERATOR_HPP

#include <htd/Globals.hpp>
#include <htd/ConstIteratorBase.hpp>
#include <htd/ConstIteratorWrapper.hpp>
#include <htd/VectorAdapterConstIteratorWrapper.hpp>

#include <memory>

namespace htd
{
    /**
     *  Wrapper for iterators of immutable collections.
     */
    template <typename T>
    class ConstIterator : public htd::ConstIteratorBase<T>
    {
        public:
            /**
             *  The difference type between two iterators.
             */
            typedef std::ptrdiff_t difference_type;

            /**
             *  The value type of the iterator.
             */
            typedef T value_type;

            /**
             *  The reference type of the iterator.
             */
            typedef const T & reference;

            /**
             *  The pointer type of the iterator.
             */
            typedef const T * pointer;

            /**
             *  The const_reference type of the iterator.
             */
            typedef const T & const_reference;

            /**
             *  The const_pointer type of the iterator.
             */
            typedef const T * const_pointer;

            /**
             *  The category of the iterator.
             */
            typedef std::forward_iterator_tag iterator_category;

            /**
             *  Constructor for an iterator pointing nowhere.
             */
            ConstIterator(void) noexcept : baseIterator_(nullptr)
            {

            }

            /**
             *  Constructor for an iterator.
             *
             *  @param[in] iterator The underlying iterator.
             */
            template <class Iter>
            ConstIterator(Iter iterator) : baseIterator_(new htd::ConstIteratorWrapper<Iter, T>(iterator))
            {

            }

            /**
             *  Constructor for an iterator.
             *
             *  @param[in] iterator The underlying iterator.
             *
             *  @note When calling this method the control over the memory region of the provided base iterator will be transferred to
             *  the new iterator wrapper. Deleting the base iterator outside the iterator wrapper or using the same base iterator in
             *  different iterator wrappers will lead to undefined behavior.
             */
            ConstIterator(htd::ConstIteratorBase<T> * iterator) noexcept : baseIterator_(iterator)
            {

            }

            /**
             *  Copy constructor for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            ConstIterator(const ConstIterator & original) noexcept : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = original.baseIterator_->clone();
                }
            }

            /**
             *  Move constructor for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            ConstIterator(ConstIterator && original) noexcept : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = std::move(original.baseIterator_);

                    original.baseIterator_ = nullptr;
                }
            }

            /**
             *  Destructor for a ConstIterator object.
             */
            virtual ~ConstIterator()
            {
                if (baseIterator_ != nullptr)
                {
                    delete baseIterator_;

                    baseIterator_ = nullptr;
                }
            }

            ConstIterator & operator++(void) noexcept override
            {
                if (baseIterator_!= nullptr)
                {
                    ++(*baseIterator_);
                }

                return *this;
            }

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            ConstIterator operator++(int) noexcept
            {
                ConstIterator ret(*baseIterator_);

                operator++();

                return ret;
            }

            /**
             *  Copy assignment operator for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            ConstIterator & operator=(const ConstIterator & original) noexcept
            {
                if (baseIterator_!= nullptr)
                {
                    delete baseIterator_;

                    baseIterator_ = nullptr;
                }

                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = original.baseIterator_->clone();
                }

                return *this;
            }

            /**
             *  Move assignment operator for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            ConstIterator & operator=(ConstIterator && original) noexcept
            {
                if (baseIterator_!= nullptr)
                {
                    delete baseIterator_;

                    baseIterator_ = nullptr;
                }

                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = std::move(original.baseIterator_);

                    original.baseIterator_ = nullptr;
                }

                return *this;
            }

            bool operator==(const htd::ConstIteratorBase<T> & rhs) const noexcept override
            {
                bool ret = false;

                const ConstIterator * o = static_cast<const ConstIterator *>(&rhs);

                if (baseIterator_ == nullptr)
                {
                    ret = o->baseIterator_ == nullptr;
                }
                else if (o->baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ == *(o->baseIterator_ );
                }

                return ret;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const ConstIterator & rhs) const noexcept
            {
                bool ret = false;

                if (baseIterator_ == nullptr)
                {
                    ret = rhs.baseIterator_ == nullptr;
                }
                else if (rhs.baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ == *(rhs.baseIterator_ );
                }

                return ret;
            }

            bool operator!=(const htd::ConstIteratorBase<T> & rhs) const noexcept override
            {
                bool ret = false;

                const ConstIterator * o = static_cast<const ConstIterator *>(&rhs);

                if (baseIterator_ == nullptr)
                {
                    ret = o->baseIterator_ != nullptr;
                }
                else if (o->baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ != *(o->baseIterator_ );
                }

                return ret;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const ConstIterator & rhs) const noexcept
            {
                bool ret = false;

                if (baseIterator_ == nullptr)
                {
                    ret = rhs.baseIterator_ != nullptr;
                }
                else if (rhs.baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ != *(rhs.baseIterator_ );
                }

                return ret;
            }

            const T * operator->(void) const override
            {
                return baseIterator_->operator->();
            }

            const T & operator*(void) const override
            {
                return baseIterator_->operator*();
            }

            ConstIterator * clone(void) const noexcept override
            {
                ConstIterator * ret = nullptr;

                if (baseIterator_ == nullptr)
                {
                    return new ConstIterator();
                }
                else
                {
                    return new ConstIterator(*this);
                }

                return ret;
            }

        private:
            htd::ConstIteratorBase<T> * baseIterator_;

            ConstIterator(const htd::ConstIteratorBase<T> & original) : baseIterator_(original.clone())
            {

            }
    };
}

#endif /* HTD_HTD_CONSTITERATOR_HPP */
