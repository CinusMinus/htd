/* 
 * File:   MultiGraph.hpp
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

#ifndef HTD_HTD_MULTIGRAPH_HPP
#define HTD_HTD_MULTIGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableMultiGraph.hpp>

#include <htd/IMutableMultiHypergraph.hpp>

namespace htd
{
    /**
     *  Default implementation of the IMutableMultiGraph interface.
     */
    class MultiGraph : public virtual htd::IMutableMultiGraph
    {
        public:
            /**
             *  Constructor for a multi-graph.
             *
             *  @param[in] manager   The management instance to which the new multi-graph belongs.
             */
            HTD_API MultiGraph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a multi-graph.
             *
             *  @param[in] manager       The management instance to which the new multi-graph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            HTD_API MultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a multi-graph.
             *
             *  @param[in] original  The original multi-graph.
             */
            HTD_API MultiGraph(const MultiGraph & original);

            /**
             *  Copy constructor for a multi-graph.
             *
             *  @param[in] original  The original multi-graph.
             */
            HTD_API MultiGraph(const htd::IMultiGraph & original);

            HTD_API virtual ~MultiGraph();
            
            HTD_API std::size_t vertexCount(void) const override;

            HTD_API std::size_t edgeCount(void) const override;

            HTD_API std::size_t edgeCount(htd::vertex_t vertex) const override;

            HTD_API bool isVertex(htd::vertex_t vertex) const override;

            HTD_API bool isEdge(htd::id_t edgeId) const override;

            HTD_API bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const override;

            HTD_API bool isEdge(const std::vector<htd::vertex_t> & elements) const override;

            HTD_API bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const override;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const override;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const override;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> vertices(void) const override;

            HTD_API void copyVerticesTo(std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t vertexAtPosition(htd::index_t index) const override;
            
            HTD_API bool isConnected(void) const override;
            
            HTD_API bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const override;

            HTD_API bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const override;
            
            HTD_API std::size_t neighborCount(htd::vertex_t vertex) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const override;

            HTD_API void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const override;

            HTD_API std::size_t isolatedVertexCount(void) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const override;

            HTD_API htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const override;

            HTD_API bool isIsolatedVertex(htd::vertex_t vertex) const override;

            HTD_API htd::ConstCollection<htd::Hyperedge> hyperedges(void) const override;

            HTD_API htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const override;

            HTD_API const htd::Hyperedge & hyperedge(htd::id_t edgeId) const override;

            HTD_API const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const override;

            HTD_API const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const override;

            HTD_API htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const override;

            HTD_API htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const override;

            HTD_API htd::vertex_t nextVertex(void) const override;

            HTD_API htd::id_t nextEdgeId(void) const override;

            HTD_API htd::vertex_t addVertex(void) override;

            HTD_API htd::vertex_t addVertices(std::size_t count) override;

            HTD_API void removeVertex(htd::vertex_t vertex) override;

            HTD_API htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) override;

            HTD_API void removeEdge(htd::id_t edgeId) override;

            HTD_API const htd::LibraryInstance * managementInstance(void) const noexcept override;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) override;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API MultiGraph * clone(void) const override;
#else
            /**
             *  Create a deep copy of the current mutable multi-graph.
             *
             *  @return A new MultiGraph object identical to the current mutable multi-graph.
             */
            HTD_API MultiGraph * clone(void) const;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const override;

            HTD_API htd::IGraphStructure * cloneGraphStructure(void) const override;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const override;

            HTD_API htd::IMutableMultiGraph * cloneMutableMultiGraph(void) const override;
#endif

            /**
             *  Copy assignment operator for a mutable multi-graph.
             *
             *  @param[in] original  The original multi-graph.
             */
            HTD_API MultiGraph & operator=(const MultiGraph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API MultiGraph & operator=(const htd::IMultiGraph & original) override;
#else
            HTD_API MultiGraph & operator=(const htd::IMultiGraph & original);

            HTD_API void assign(const htd::IMultiGraph & original) override;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_MULTIGRAPH_HPP */
