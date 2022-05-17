/* 
 * File:   BucketEliminationGraphDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>

#include <htd/IGraphDecompositionManipulationOperation.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IPreprocessedGraph.hpp>

#include <utility>

namespace htd
{
    /**
     *  Default implementation of the IGraphDecompositionAlgorithm interface based on bucket elimination.
     */
    class BucketEliminationGraphDecompositionAlgorithm : public htd::IGraphDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a graph decomposition algorithm based on bucket elimination.
             *
             *  @param[in] manager  The management instance to which the new algorithm belongs.
             */
            HTD_API BucketEliminationGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a graph decomposition algorithm based on bucket elimination.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manager                  The management instance to which the new algorithm belongs.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API BucketEliminationGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            HTD_API virtual ~BucketEliminationGraphDecompositionAlgorithm();

            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const override;

            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const override;

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
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the decomposition.
             *  @param[in] maxIterationCount        The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
             *
             *  @note The bag size which is compared to maxBagSize is the maximum bag size of the decomposition BEFORE the manipulation operations are applied.
             *  Therefore, the result of this function may have a maximum bag size exceeding maxBagSize if the requested manipulations create larger bags.
             *
             *  @return A pair consisting of the new IGraphDecomposition object representing the decomposition of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
             */
            HTD_API std::pair<htd::IGraphDecomposition *, std::size_t> computeDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the decomposition.
             *  @param[in] maxIterationCount        The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @note The bag size which is compared to maxBagSize is the maximum bag size of the decomposition BEFORE the manipulation operations are applied.
             *  Therefore, the result of this function may have a maximum bag size exceeding maxBagSize if the requested manipulations create larger bags.
             *
             *  @return A pair consisting of the new IGraphDecomposition object representing the decomposition of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
             */
            HTD_API std::pair<htd::IGraphDecomposition *, std::size_t> computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize, std::size_t maxIterationCount) const;

            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const override;

            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const override;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] preprocessedGraph            The input graph in preprocessed format.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the decomposition.
             *  @param[in] maxIterationCount        The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
             *
             *  @note The bag size which is compared to maxBagSize is the maximum bag size of the decomposition BEFORE the manipulation operations are applied.
             *  Therefore, the result of this function may have a maximum bag size exceeding maxBagSize if the requested manipulations create larger bags.
             *
             *  @return A pair consisting of the new IGraphDecomposition object representing the decomposition of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
             */
            HTD_API std::pair<htd::IGraphDecomposition *, std::size_t> computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the decomposition.
             *  @param[in] maxIterationCount        The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @note The bag size which is compared to maxBagSize is the maximum bag size of the decomposition BEFORE the manipulation operations are applied.
             *  Therefore, the result of this function may have a maximum bag size exceeding maxBagSize if the requested manipulations create larger bags.
             *
             *  @return A pair consisting of the new IGraphDecomposition object representing the decomposition of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
             */
            HTD_API std::pair<htd::IGraphDecomposition *, std::size_t> computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize, std::size_t maxIterationCount) const;

            /**
             *  Set the ordering algorithm which shall be used to compute the vertex elimination ordering.
             *
             *  @param[in] algorithm    The ordering algorithm which shall be used to compute the vertex elimination ordering.
             *
             *  @note When calling this method the control over the memory region of the ordering algorithm is transferred to the decomposition
             *  algorithm. Deleting the ordering algorithm provided to this method outside the decomposition algorithm or assigning the same
             *  ordering algorithm multiple times will lead to undefined behavior.
             */
            HTD_API void setOrderingAlgorithm(htd::IOrderingAlgorithm * algorithm);

            HTD_API void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) override;

            HTD_API void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) override;

            HTD_API void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) override;

            HTD_API bool isSafelyInterruptible(void) const override;

            HTD_API bool isComputeInducedEdgesEnabled(void) const override;

            HTD_API void setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled) override;

            HTD_API const htd::LibraryInstance * managementInstance(void) const noexcept override;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) override;

            /**
             *  Check whether the computed decompositions shall contain only subset-maximal bags.
             *
             *  @return A boolean flag indicating whether the computed decompositions shall contain only subset-maximal bags.
             */
            HTD_API bool isCompressionEnabled(void) const;

            /**
             *  Set whether the computed decompositions shall contain only subset-maximal bags.
             *
             *  @param[in] compressionEnabled   A boolean flag indicating whether the computed decompositions shall contain only subset-maximal bags.
             */
            HTD_API void setCompressionEnabled(bool compressionEnabled);

            HTD_API BucketEliminationGraphDecompositionAlgorithm * clone(void) const override;

        protected:
            /**
             *  Copy assignment operator for a graph decomposition algorithm based on bucket elimination.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            BucketEliminationGraphDecompositionAlgorithm & operator=(const BucketEliminationGraphDecompositionAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP */
