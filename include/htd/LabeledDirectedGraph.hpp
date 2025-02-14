/*
 * File:   LabeledDirectedGraph.hpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPH_HPP
#define HTD_HTD_LABELEDDIRECTEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/IMutableLabeledDirectedGraph.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledDirectedGraph interface.
     */
    class LabeledDirectedGraph : public htd::LabeledGraphType<htd::DirectedGraph>, public virtual htd::IMutableLabeledDirectedGraph
    {
        public:
            /**
             *  Constructor for a labeled directed graph.
             *
             *  @param[in] manager   The management instance to which the new labeled directed graph belongs.
             */
            HTD_API LabeledDirectedGraph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a labeled directed graph.
             *
             *  @param[in] manager       The management instance to which the new labeled directed graph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            HTD_API LabeledDirectedGraph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a labeled directed graph.
             *
             *  @param[in] original  The original labeled directed graph.
             */
            HTD_API LabeledDirectedGraph(const LabeledDirectedGraph & original);

            /**
             *  Copy constructor for a directed graph.
             *
             *  @param[in] original  The original directed graph.
             */
            HTD_API LabeledDirectedGraph(const htd::IDirectedGraph & original);

            /**
             *  Copy constructor for a labeled directed graph.
             *
             *  @param[in] original  The original labeled directed graph.
             */
            HTD_API LabeledDirectedGraph(const htd::ILabeledDirectedGraph & original);
            
            HTD_API virtual ~LabeledDirectedGraph();

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
            HTD_API LabeledDirectedGraph * clone(void) const override;
#else
            /**
             *  Create a deep copy of the current mutable labeled directed graph.
             *
             *  @return A new LabeledDirectedGraph object identical to the current mutable labeled directed graph.
             */
            HTD_API LabeledDirectedGraph * clone(void) const;

            HTD_API htd::IGraph * cloneGraph(void) const override;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const override;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const override;

            HTD_API htd::IDirectedGraph * cloneDirectedGraph(void) const override;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const override;

            HTD_API htd::IDirectedMultiGraph * cloneDirectedMultiGraph(void) const override;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const override;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const override;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const override;

            HTD_API htd::ILabeledDirectedGraph * cloneLabeledDirectedGraph(void) const override;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const override;

            HTD_API htd::ILabeledDirectedMultiGraph * cloneLabeledDirectedMultiGraph(void) const override;

            HTD_API htd::IMutableDirectedGraph * cloneMutableDirectedGraph(void) const override;

            HTD_API htd::IMutableLabeledDirectedGraph * cloneMutableLabeledDirectedGraph(void) const override;
#endif

            /**
             *  Copy assignment operator for a mutable labeled directed graph.
             *
             *  @param[in] original  The original labeled directed graph.
             */
            HTD_API LabeledDirectedGraph & operator=(const LabeledDirectedGraph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledDirectedGraph & operator=(const htd::IDirectedGraph & original) override;

            HTD_API LabeledDirectedGraph & operator=(const htd::ILabeledDirectedGraph & original) override;
#else
            HTD_API LabeledDirectedGraph & operator=(const htd::IDirectedGraph & original);

            HTD_API LabeledDirectedGraph & operator=(const htd::ILabeledDirectedGraph & original);

            HTD_API void assign(const htd::IDirectedGraph & original) override;

            HTD_API void assign(const htd::ILabeledDirectedGraph & original) override;
#endif
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPH_HPP */
