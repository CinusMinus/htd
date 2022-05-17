/*
 * File:   LabeledDirectedMultiGraph.hpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP
#define HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/DirectedMultiGraph.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/IMutableLabeledDirectedMultiGraph.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledDirectedMultiGraph interface.
     */
    class LabeledDirectedMultiGraph : public htd::LabeledGraphType<htd::DirectedMultiGraph>, public virtual htd::IMutableLabeledDirectedMultiGraph
    {
        public:
            /**
             *  Constructor for a labeled directed multi-graph.
             *
             *  @param[in] manager   The management instance to which the new labeled multi-graph belongs.
             */
            HTD_API LabeledDirectedMultiGraph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a labeled directed multi-graph.
             *
             *  @param[in] manager       The management instance to which the new labeled multi-graph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            HTD_API LabeledDirectedMultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a labeled directed multi-graph.
             *
             *  @param[in] original  The original labeled directed multi-graph.
             */
            HTD_API LabeledDirectedMultiGraph(const LabeledDirectedMultiGraph & original);

            /**
             *  Copy constructor for a directed multi-graph.
             *
             *  @param[in] original  The original directed multi-graph.
             */
            HTD_API LabeledDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

            /**
             *  Copy constructor for a labeled directed multi-graph.
             *
             *  @param[in] original  The original labeled directed multi-graph.
             */
            HTD_API LabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original);
            
            HTD_API virtual ~LabeledDirectedMultiGraph();

            HTD_API void removeVertex(htd::vertex_t vertex) override;

            HTD_API void removeEdge(htd::id_t edgeId) override;

            HTD_API const htd::ILabelingCollection & labelings(void) const override;

            HTD_API std::size_t labelCount(void) const override;

            HTD_API htd::ConstCollection<std::string> labelNames(void) const override;

            HTD_API const std::string & labelNameAtPosition(htd::index_t index) const override;

            HTD_API bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const override;

            HTD_API bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const override;

            HTD_API const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const override;

            HTD_API const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const override;

            HTD_API void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) override;

            HTD_API void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) override;

            HTD_API void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) override;

            HTD_API void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) override;

            HTD_API void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) override;

            HTD_API void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) override;

            HTD_API void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) override;

            HTD_API void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) override;

            HTD_API htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) override;

            HTD_API htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) override;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledDirectedMultiGraph * clone(void) const override;
#else
            /**
             *  Create a deep copy of the current mutable labeled directed multi-graph.
             *
             *  @return A new LabeledDirectedMultiGraph object identical to the current mutable labeled directed multi-graph.
             */
            HTD_API LabeledDirectedMultiGraph * clone(void) const;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const override;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const override;

            HTD_API htd::IDirectedMultiGraph * cloneDirectedMultiGraph(void) const override;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const override;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const override;

            HTD_API htd::ILabeledDirectedMultiGraph * cloneLabeledDirectedMultiGraph(void) const override;

            HTD_API htd::IMutableDirectedMultiGraph * cloneMutableDirectedMultiGraph(void) const override;

            HTD_API htd::IMutableLabeledDirectedMultiGraph * cloneMutableLabeledDirectedMultiGraph(void) const override;
#endif

            /**
             *  Copy assignment operator for a mutable labeled directed multi-graph.
             *
             *  @param[in] original  The original labeled directed multi-graph.
             */
            HTD_API LabeledDirectedMultiGraph & operator=(const LabeledDirectedMultiGraph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledDirectedMultiGraph & operator=(const htd::IDirectedMultiGraph & original) override;

            HTD_API LabeledDirectedMultiGraph & operator=(const htd::ILabeledDirectedMultiGraph & original) override;
#else
            HTD_API LabeledDirectedMultiGraph & operator=(const htd::IDirectedMultiGraph & original);

            HTD_API LabeledDirectedMultiGraph & operator=(const htd::ILabeledDirectedMultiGraph & original);

            HTD_API void assign(const htd::IDirectedMultiGraph & original) override;

            HTD_API void assign(const htd::ILabeledDirectedMultiGraph & original) override;
#endif
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP */
