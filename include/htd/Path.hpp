/* 
 * File:   Path.hpp
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

#ifndef HTD_HTD_PATH_HPP
#define HTD_HTD_PATH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutablePath.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    /**
     *  Default implementation of the IMutablePath interface.
     */
    class Path : public virtual htd::IMutablePath
    {
        public:
            /**
             *  Constructor for a path.
             */
            HTD_API Path(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a path.
             *
             *  @param[in] original  The original path.
             */
            HTD_API Path(const Path & original);

            /**
             *  Copy constructor for a path.
             *
             *  @param[in] original  The original path.
             */
            HTD_API Path(const htd::IPath & original);
            
            HTD_API virtual ~Path();
            
            HTD_API std::size_t vertexCount(void) const override;

            HTD_API std::size_t vertexCount(htd::vertex_t subPathRoot) const override;

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

            HTD_API bool isConnected(void) const override;
            
            HTD_API bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const override;

            HTD_API std::size_t neighborCount(htd::vertex_t vertex) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const override;

            HTD_API void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const override;

            HTD_API bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> vertices(void) const override;

            /**
             *  Access the vector of all vertices in the tree.
             *
             *  @return The vector of all vertices in the tree sorted in ascending order.
             */
            HTD_API const std::vector<htd::vertex_t> & vertexVector(void) const;

            HTD_API void copyVerticesTo(std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t vertexAtPosition(htd::index_t index) const override;

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

            HTD_API htd::vertex_t root(void) const override;

            HTD_API bool isRoot(htd::vertex_t vertex) const override;

            HTD_API std::size_t leafCount(void) const noexcept override;

            HTD_API htd::ConstCollection<htd::vertex_t> leaves(void) const override;

            HTD_API void copyLeavesTo(std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t leaf(void) const override;

            HTD_API htd::vertex_t leafAtPosition(htd::index_t index) const override;

            HTD_API bool isLeaf(htd::vertex_t vertex) const override;

            HTD_API htd::vertex_t parent(htd::vertex_t vertex) const override;

            HTD_API bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const override;

            HTD_API std::size_t childCount(htd::vertex_t vertex) const override;

            HTD_API htd::ConstCollection<htd::vertex_t> children(htd::vertex_t vertex) const override;

            HTD_API void copyChildrenTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const override;

            HTD_API htd::vertex_t child(htd::vertex_t vertex) const override;

            HTD_API htd::vertex_t childAtPosition(htd::vertex_t vertex, htd::index_t index) const override;

            HTD_API bool isChild(htd::vertex_t vertex, htd::vertex_t child) const override;

            HTD_API std::size_t height(void) const override;

            HTD_API std::size_t height(htd::vertex_t vertex) const override;

            HTD_API std::size_t depth(htd::vertex_t vertex) const override;

            HTD_API htd::vertex_t nextVertex(void) const override;

            HTD_API htd::id_t nextEdgeId(void) const override;

            HTD_API void removeVertex(htd::vertex_t vertex) override;

            HTD_API void removeSubpath(htd::vertex_t subpathRoot) override;

            HTD_API htd::vertex_t insertRoot(void) override;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex) override;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex) override;

            HTD_API void removeChild(htd::vertex_t vertex) override;

            HTD_API void removeChild(htd::vertex_t vertex, htd::vertex_t child) override;

            HTD_API void swapWithParent(htd::vertex_t vertex) override;

            HTD_API const htd::LibraryInstance * managementInstance(void) const noexcept override;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) override;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API Path * clone(void) const override;
#else
            /**
             *  Create a deep copy of the current mutable path.
             *
             *  @return A new Path object identical to the current mutable path.
             */
            HTD_API Path * clone(void) const;

            HTD_API htd::IPath * clonePath(void) const override;

            HTD_API htd::ITree * cloneTree(void) const override;

            HTD_API htd::IGraph * cloneGraph(void) const override;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const override;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const override;

            HTD_API htd::IGraphStructure * cloneGraphStructure(void) const override;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const override;

            HTD_API htd::IMutablePath * cloneMutablePath(void) const override;
#endif

            /**
             *  Copy assignment operator for a mutable path.
             *
             *  @param[in] original  The original path.
             */
            HTD_API Path & operator=(const Path & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API Path & operator=(const htd::IPath & original) override;
#else
            HTD_API Path & operator=(const htd::IPath & original);

            HTD_API void assign(const htd::IPath & original) override;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_PATH_HPP */
