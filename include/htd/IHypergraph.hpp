/* 
 * File:   IHypergraph.hpp
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

#ifndef HTD_HTD_IHYPERGRAPH_HPP
#define HTD_HTD_IHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>

#include <cstdlib>
#include <vector>

namespace htd
{
    /**
     * Interface for classes which represent hypergraphs.
     */
    class IHypergraph : public virtual htd::IMultiHypergraph
    {
        public:
            virtual ~IHypergraph() = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current hypergraph.
             *
             *  @return A new IHypergraph object identical to the current hypergraph.
             */
            virtual IHypergraph * clone(void) const override = 0;
#else
            /**
             *  Create a deep copy of the current hypergraph.
             *
             *  @return A new IHypergraph object identical to the current hypergraph.
             */
            virtual IHypergraph * cloneHypergraph(void) const = 0;
#endif
    };

    inline htd::IHypergraph::~IHypergraph() { }
}

#endif /* HTD_HTD_IHYPERGRAPH_HPP */
