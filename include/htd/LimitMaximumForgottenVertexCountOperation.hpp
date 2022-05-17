/*
 * File:   LimitMaximumForgottenVertexCountOperation.hpp
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

#ifndef HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_HPP
#define HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Implementation of the IDecompositionManipulationOperation interface which manipulates given
     *  tree and path decompositions in such a way that for each decomposition node the cardinality
     *  of the set difference between the set union of the node's child bags and the node's bag is
     *  bounded by the given limit.
     */
    class LimitMaximumForgottenVertexCountOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constructor for a new manipulation operation of type LimitMaximumForgottenVertexCountOperation.
             *
             *  @param[in] manager   The management instance to which the new manipulation operation belongs.
             *  @param[in] limit    The maximum number of forgotten vertices for a decomposition node.
             */
            HTD_API LimitMaximumForgottenVertexCountOperation(const htd::LibraryInstance * const manager, std::size_t limit);

            HTD_API virtual ~LimitMaximumForgottenVertexCountOperation();

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const override;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const override;

            HTD_API bool isLocalOperation(void) const override;

            HTD_API bool createsTreeNodes(void) const override;

            HTD_API bool removesTreeNodes(void) const override;

            HTD_API bool modifiesBagContents(void) const override;

            HTD_API bool createsSubsetMaximalBags(void) const override;

            HTD_API bool createsLocationDependendLabels(void) const override;

            HTD_API const htd::LibraryInstance * managementInstance(void) const noexcept override;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) override;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LimitMaximumForgottenVertexCountOperation * clone(void) const override;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new LimitMaximumForgottenVertexCountOperation object identical to the current decomposition manipulation operation.
             */
            HTD_API LimitMaximumForgottenVertexCountOperation * clone(void) const;

            HTD_API htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const override;

            HTD_API htd::IPathDecompositionManipulationOperation * clonePathDecompositionManipulationOperation(void) const override;

            HTD_API htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const override;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_HPP */
