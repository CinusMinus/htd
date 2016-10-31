/* 
 * File:   PostProcessingPathDecompositionAlgorithm.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>

#include <cstdarg>
#include <vector>

namespace htd
{
    /**
     *  Default implementation of the IPathDecompositionAlgorithm interface based on post-processing a tree decomposition.
     */
    class PostProcessingPathDecompositionAlgorithm : public virtual htd::IPathDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a path decomposition algorithm based on the post-processing of a tree decomposition.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API PostProcessingPathDecompositionAlgorithm(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a path decomposition algorithm based on the post-processing of a tree decomposition.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manager                   The management instance to which the new algorithm belongs.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API PostProcessingPathDecompositionAlgorithm(const htd::LibraryInstance * const manager, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            HTD_API virtual ~PostProcessingPathDecompositionAlgorithm();

            HTD_API htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            HTD_API htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new IPathDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            HTD_API void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            HTD_API void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API bool isSafelyInterruptible(void) const HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API PostProcessingPathDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a path decomposition algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            PostProcessingPathDecompositionAlgorithm & operator=(const PostProcessingPathDecompositionAlgorithm &) { return *this; }

            /**
             *  Compute a path decomposition based on a given tree decomposition.
             *
             *  @param[in] decomposition    The tree decomposition which shall be transformed.
             *
             *  @return A new IMutablePathDecomposition object constructed from the given tree decomposition.
             */
            htd::IMutablePathDecomposition * toPathDecomposition(htd::IMutableTreeDecomposition && decomposition) const;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP */
