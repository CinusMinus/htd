/* 
 * File:   AdvancedMinFillOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_CPP
#define	HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/AdvancedMinFillOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::AdvancedMinFillOrderingAlgorithm.
 */
struct htd::AdvancedMinFillOrderingAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  Compute the number of edges between a set of vertices.
     *
     *  @param[in] availableNeighborhoods   The neighborhoods of the provided vertices.
     *  @param[in] vertices                 The vertices for which the number of edges shall be returned.
     *
     *  @return The number of edges between the provided vertices.
     */
    std::size_t computeEdgeCount(const std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices) const HTD_NOEXCEPT;
};

htd::AdvancedMinFillOrderingAlgorithm::AdvancedMinFillOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}

htd::AdvancedMinFillOrderingAlgorithm::~AdvancedMinFillOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::AdvancedMinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::VectorAdapter<htd::vertex_t> ret;

    writeOrderingTo(graph, ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::AdvancedMinFillOrderingAlgorithm::writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_NOEXCEPT
{
    std::size_t size = graph.vertexCount();

    std::size_t minFill = (std::size_t)-1;
    std::size_t minDegree = (std::size_t)-1;

    std::unordered_set<htd::vertex_t> pool;

    std::unordered_set<htd::vertex_t> vertices(size);

    std::unordered_map<htd::vertex_t, htd::state_t> updateStatus(size);

    std::unordered_map<htd::vertex_t, std::size_t> requiredFillAmount(size);
    
    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> neighborhood(size);

    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> existingNeighbors(size);
    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> additionalNeighbors(size);
    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> unaffectedNeighbors(size);
    
    htd::fillSet(graph.vertices(), vertices);

    std::vector<htd::vertex_t> newNeighborhood;
    
    std::vector<htd::vertex_t> affectedVertices;
    affectedVertices.reserve(size);

    std::size_t totalFill = 0;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = vertices.begin(); it != vertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        auto & currentNeighborhood = neighborhood[vertex];

        graph.copyNeighborsTo(currentNeighborhood, vertex);

        auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);
        
        if (position == currentNeighborhood.end() || *position != vertex)
        {
            currentNeighborhood.insert(position, vertex);
        }

        updateStatus[vertex] = htd::State::UNKNOWN;
    }

    for (auto it = vertices.begin(); it != vertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        auto & currentNeighborhood = neighborhood.at(vertex);
        
        std::size_t currentFillValue = ((currentNeighborhood.size() * (currentNeighborhood.size() - 1)) / 2) - implementation_->computeEdgeCount(neighborhood, currentNeighborhood);

        if (currentFillValue <= minFill)
        {
            std::size_t currentVertexDegree = neighborhood.at(vertex).size() - 1;

            if (currentFillValue < minFill)
            {
                minFill = currentFillValue;

                minDegree = currentVertexDegree;

                pool.clear();
            }

            if (currentVertexDegree <= minDegree)
            {
                if (currentVertexDegree < minDegree)
                {
                    minDegree = currentVertexDegree;

                    pool.clear();
                }

                pool.insert(vertex);
            }
        }

        requiredFillAmount[vertex] = currentFillValue;

        DEBUGGING_CODE_LEVEL2(
        std::cout << "Vertex " << vertex << ":" << std::endl;
        htd::print(currentNeighborhood, std::cout, false);
        std::cout << std::endl;
        std::size_t neighborhoodSize = currentNeighborhood.size();
        std::cout << "   INITIAL EDGE COUNT " << vertex << ": " << computeEdgeCount(neighborhood, neighborhood[vertex]) << std::endl;
        std::cout << "   MAXIMUM EDGE COUNT " << vertex << ": " << (neighborhoodSize * (neighborhoodSize - 1)) / 2 << std::endl;
        std::cout << "   INITIAL FILL VALUE " << vertex << ": " << requiredFillAmount[vertex] << std::endl;
        )

        totalFill += currentFillValue;
    }
    
    while (totalFill > 0 && !managementInstance.isTerminated())
    {
        if (pool.size() == 0)
        {
            minFill = (std::size_t)-1;

            minDegree = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                std::size_t currentFillValue = requiredFillAmount.at(vertex);

                if (currentFillValue <= minFill)
                {
                    std::size_t currentVertexDegree = neighborhood.at(vertex).size() - 1;

                    if (currentFillValue < minFill)
                    {
                        minFill = currentFillValue;

                        minDegree = currentVertexDegree;

                        pool.clear();
                    }

                    if (currentVertexDegree <= minDegree)
                    {
                        if (currentVertexDegree < minDegree)
                        {
                            minDegree = currentVertexDegree;

                            pool.clear();
                        }

                        pool.insert(vertex);
                    }
                } 
            }
        }

        htd::vertex_t selectedVertex = selectRandomElement<htd::vertex_t>(pool);

        auto & selectedNeighborhood = neighborhood.at(selectedVertex);

        pool.erase(selectedVertex);

        updateStatus.at(selectedVertex) = 4;
        
        affectedVertices.clear();

        totalFill -= minFill;

        if (requiredFillAmount.at(selectedVertex) == 0)
        {
            for (auto vertex : selectedNeighborhood)
            {
                if (vertex != selectedVertex)
                {
                    auto & currentNeighborhood = neighborhood.at(vertex);

                    std::size_t fillReduction = htd::set_difference_size(currentNeighborhood.begin(), currentNeighborhood.end(), selectedNeighborhood.begin(), selectedNeighborhood.end());

                    requiredFillAmount[vertex] -= fillReduction;

                    totalFill -= fillReduction;

                    /* Because 'vertex' is a neighbor of 'selectedVertex', std::lower_bound will always find 'selectedVertex' in 'currentNeighborhood'. */
                    // coverity[use_iterator]
                    currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));
                }
            }
        }
        else
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    if (updateStatus.at(neighbor) == 0)
                    {
                        htd::decompose_sets(selectedNeighborhood, neighborhood.at(neighbor), selectedVertex,
                                            additionalNeighbors[neighbor],
                                            unaffectedNeighbors[neighbor],
                                            existingNeighbors[neighbor]);
                    }

                    updateStatus.at(neighbor) |= 1;

                    for (auto affectedVertex : neighborhood.at(neighbor))
                    {
                        htd::state_t currentUpdateStatus = updateStatus.at(affectedVertex);

                        if (currentUpdateStatus < 2)
                        {
                            if (currentUpdateStatus == 0)
                            {
                                htd::decompose_sets(selectedNeighborhood, neighborhood.at(affectedVertex), selectedVertex,
                                                    additionalNeighbors[affectedVertex],
                                                    unaffectedNeighbors[affectedVertex],
                                                    existingNeighbors[affectedVertex]);
                            }

                            affectedVertices.push_back(affectedVertex);
                            
                            updateStatus.at(affectedVertex) |= 2;
                        }
                    }
                }
            }

            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                if (vertex != selectedVertex)
                {
                    auto & currentNeighborhood = neighborhood.at(vertex);
                    auto & currentUnaffectedNeighborhood = unaffectedNeighbors.at(vertex);
                    auto & currentAdditionalNeighborhood = additionalNeighbors.at(vertex);

                    std::size_t additionalNeighborCount = currentAdditionalNeighborhood.size();

                    if (additionalNeighborCount > 0)
                    {
                        if (additionalNeighborCount == 1)
                        {
                            auto first = currentNeighborhood.begin();
                            auto last = currentNeighborhood.end();
                            
                            htd::vertex_t newVertex = currentAdditionalNeighborhood[0];

                            if (newVertex < selectedVertex)
                            {
                                if (selectedVertex - newVertex == 1)
                                {
                                    *std::lower_bound(first, last, selectedVertex) = newVertex;
                                }
                                else
                                {
                                    htd::index_t position1 = std::distance(first, std::lower_bound(first, last, newVertex));
                                    htd::index_t position2 = std::distance(first, std::lower_bound(first + position1, last, selectedVertex));
                                    
                                    currentNeighborhood.erase(first + position2);
                                    currentNeighborhood.insert(currentNeighborhood.begin() + position1, newVertex);
                                }
                            }
                            else
                            {
                                if (newVertex - selectedVertex == 1)
                                {
                                    *std::lower_bound(first, last, selectedVertex) = newVertex;
                                }
                                else
                                {
                                    htd::index_t position1 = std::distance(first, std::lower_bound(first, last, selectedVertex));

                                    first = currentNeighborhood.erase(first + position1);

                                    currentNeighborhood.insert(std::lower_bound(first, currentNeighborhood.end(), newVertex), newVertex);
                                }
                            }
                        }
                        else
                        {
                            htd::merge(currentNeighborhood, currentAdditionalNeighborhood, selectedVertex, newNeighborhood);

                            std::swap(currentNeighborhood, newNeighborhood);

                            newNeighborhood.clear();
                        }
                    }
                    else
                    {
                        currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));
                    }

                    std::size_t tmp = requiredFillAmount.at(vertex);

                    if (additionalNeighborCount > 0 || tmp > 0)
                    {
                        std::size_t unaffectedNeighborCount = currentUnaffectedNeighborhood.size();

                        if (unaffectedNeighborCount > 0)
                        {
                            if (additionalNeighborCount == 0)
                            {
                                auto & relevantNeighborhood = existingNeighbors.at(vertex);

                                std::size_t remainder = relevantNeighborhood.size();
    
                                for (auto it = relevantNeighborhood.begin(); remainder > 0 && tmp > unaffectedNeighborCount; --remainder)
                                {
                                    htd::vertex_t vertex2 = *it;

                                    auto & currentAdditionalNeighborhood2 = additionalNeighbors.at(vertex2);

                                    it++;

                                    std::size_t fillReduction = htd::set_intersection_size(it, relevantNeighborhood.end(), std::upper_bound(currentAdditionalNeighborhood2.begin(), currentAdditionalNeighborhood2.end(), vertex2), currentAdditionalNeighborhood2.end());

                                    tmp -= fillReduction;

                                    totalFill -= fillReduction;
                                }

                                tmp -= unaffectedNeighborCount;

                                totalFill -= unaffectedNeighborCount;

                                //TODO
                                updateStatus.at(vertex) = 0;

                                if (tmp <= minFill)
                                {
                                    std::size_t currentVertexDegree = currentNeighborhood.size() - 1;

                                    if (tmp < minFill)
                                    {
                                        minFill = tmp;

                                        minDegree = currentVertexDegree;

                                        pool.clear();
                                    }

                                    if (currentVertexDegree <= minDegree)
                                    {
                                        if (currentVertexDegree < minDegree)
                                        {
                                            minDegree = currentVertexDegree;

                                            pool.clear();
                                        }

                                        pool.insert(vertex);
                                    }
                                }
                            }
                            else
                            {
                                std::size_t fillIncrease = 0;

                                for (htd::vertex_t unaffectedVertex : currentUnaffectedNeighborhood)
                                {
                                    auto & affectedVertices = existingNeighbors.at(unaffectedVertex);

                                    fillIncrease += htd::set_difference_size(currentAdditionalNeighborhood.begin(),
                                                                             currentAdditionalNeighborhood.end(),
                                                                             affectedVertices.begin(),
                                                                             affectedVertices.end()) - 1;
                                }

                                if (fillIncrease > 0)
                                {
                                    pool.erase(vertex);

                                    tmp += fillIncrease;

                                    totalFill += fillIncrease;
                                }

                                updateStatus.at(vertex) &= ~1;

                                if (updateStatus.at(vertex) == 0)
                                {
                                    std::size_t currentVertexDegree = currentNeighborhood.size() - 1;

                                    if (tmp <= minFill)
                                    {
                                        if (tmp < minFill)
                                        {
                                            minFill = tmp;

                                            minDegree = currentVertexDegree;

                                            pool.clear();
                                        }

                                        if (currentVertexDegree <= minDegree)
                                        {
                                            if (currentVertexDegree < minDegree)
                                            {
                                                minDegree = currentVertexDegree;

                                                pool.clear();
                                            }

                                            pool.insert(vertex);
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            totalFill -= tmp;

                            tmp = 0;

                            //TODO
                            updateStatus[vertex] = 0;

                            std::size_t currentVertexDegree = currentNeighborhood.size() - 1;

                            if (tmp < minFill)
                            {
                                minFill = tmp;

                                minDegree = currentVertexDegree;

                                pool.clear();
                            }

                            if (currentVertexDegree <= minDegree)
                            {
                                if (currentVertexDegree < minDegree)
                                {
                                    minDegree = currentVertexDegree;

                                    pool.clear();
                                }

                                pool.insert(vertex);
                            }
                        }

                        requiredFillAmount.at(vertex) = tmp;
                    }
                    else
                    {
                        updateStatus.at(vertex) = 0;
                    }
                }
            }

            for (htd::vertex_t vertex : affectedVertices)
            {
                if (updateStatus.at(vertex) == 2)
                {
                    std::size_t tmp = requiredFillAmount.at(vertex);

                    if (unaffectedNeighbors.at(vertex).size() > 0 && tmp > 0)
                    {
                        auto & relevantNeighborhood = existingNeighbors.at(vertex);

                        std::size_t remainder = relevantNeighborhood.size();
                        
                        for (auto it = relevantNeighborhood.begin(); remainder > 0 && tmp > 0; --remainder)
                        {
                            htd::vertex_t vertex2 = *it;

                            auto & currentAdditionalNeighborhood2 = additionalNeighbors.at(vertex2);

                            ++it;

                            std::size_t fillReduction = htd::set_intersection_size(it, relevantNeighborhood.end(), std::upper_bound(currentAdditionalNeighborhood2.begin(), currentAdditionalNeighborhood2.end(), vertex2), currentAdditionalNeighborhood2.end());

                            tmp -= fillReduction;

                            totalFill -= fillReduction;
                        }

                        if (tmp <= minFill)
                        {
                            std::size_t currentVertexDegree = neighborhood.at(vertex).size() - 1;

                            if (tmp < minFill)
                            {
                                minFill = tmp;

                                minDegree = currentVertexDegree;

                                pool.clear();
                            }

                            if (currentVertexDegree <= minDegree)
                            {
                                if (currentVertexDegree < minDegree)
                                {
                                    minDegree = currentVertexDegree;

                                    pool.clear();
                                }

                                pool.insert(vertex);
                            }
                        }
                    }
                    else
                    {
                        totalFill -= tmp;

                        tmp = 0;

                        std::size_t currentVertexDegree = neighborhood.at(vertex).size() - 1;

                        if (tmp < minFill)
                        {
                            minFill = tmp;

                            minDegree = currentVertexDegree;

                            pool.clear();
                        }

                        if (currentVertexDegree <= minDegree)
                        {
                            if (currentVertexDegree < minDegree)
                            {
                                minDegree = currentVertexDegree;

                                pool.clear();
                            }

                            pool.insert(vertex);
                        }
                    }

                    requiredFillAmount.at(vertex) = tmp;
                }
            }

            for (auto vertex : selectedNeighborhood)
            {
                additionalNeighbors[vertex].clear();
                unaffectedNeighbors[vertex].clear();
                existingNeighbors[vertex].clear();
            }

            for (auto vertex : affectedVertices)
            {
                if (updateStatus.at(vertex) == 2)
                {
                    additionalNeighbors[vertex].clear();
                    unaffectedNeighbors[vertex].clear();
                    existingNeighbors[vertex].clear();

                    updateStatus.at(vertex) = 0;
                }
            }
        }

        selectedNeighborhood.clear();
        
        vertices.erase(selectedVertex);

        target.push_back(selectedVertex);

        size--;

//#define VERIFY
#ifdef VERIFY
        std::cout << "CHECK (ELIMINATED=" << selectedVertex << ", FILL=" << requiredFillAmount[selectedVertex] << "): " << std::endl;
        
        std::size_t minFill2 = (std::size_t)-1;

        std::size_t totalFill2 = 0;

        for (htd::vertex_t vertex : vertices)
        {
            auto & currentNeighborhood = neighborhood[vertex];

            std::size_t neighborCount = currentNeighborhood.size();

            long actual = requiredFillAmount[vertex];

            long maximumEdges = (neighborCount * (neighborCount - 1)) / 2;
            long existingEdges = computeEdgeCount(neighborhood, currentNeighborhood);

            long expected = maximumEdges - existingEdges;

            if (actual != expected)
            {
                std::cout << "ERROR!!! Vertex " << vertex << " (Expected: " << expected << ", Actual: " << actual << ")" << std::endl;

                std::cout << "VERTEX " << vertex << ":" << std::endl;
                std::cout << "   NEIGHBORHOOD:   ";
                htd::print(currentNeighborhood, false);
                std::cout << std::endl;
                for (auto vertex2 : currentNeighborhood)
                {
                    if (vertex2 != vertex)
                    {
                        std::cout << "   NEIGHBORHOOD " << vertex2 << ": ";
                        htd::print(neighborhood[vertex2], false);
                        std::cout << std::endl;
                    }
                }
                std::cout << "EDGES " << vertex << ": " << existingEdges << "/" << maximumEdges << std::endl;

                std::exit(1);
            }

            if (actual < minFill2 && !pool.empty())
            {
                minFill2 = actual;
            }

            totalFill2 += expected;
        }

        /*
        for (htd::vertex_t vertex : vertices)
        {
            std::cout << "   " << vertex << ": " << requiredFillAmount.at(vertex) << std::endl;
        }
        */

        if (minFill != minFill2 && !pool.empty())
        {
            std::cout << "ERROR: MIN FILL " << minFill << " != " << minFill2 << std::endl;

            std::exit(1);
        }

        if (totalFill != totalFill2)
        {
            std::cout << "ERROR: TOTAL FILL " << totalFill << " != " << totalFill2 << std::endl;

            std::exit(1);
        };

        for (htd::vertex_t vertex : pool)
        {
            std::cout << "POOL VERTEX: " << vertex << "   " << requiredFillAmount[vertex] << std::endl;
        }

        std::cout << "TOTAL FILL: " << totalFill << std::endl;

        std::cout << std::endl << std::endl;
#endif
    }

    std::copy(vertices.begin(), vertices.end(), std::back_inserter(target));

    DEBUGGING_CODE_LEVEL2(std::cout << std::endl;)
}

std::size_t htd::AdvancedMinFillOrderingAlgorithm::Implementation::computeEdgeCount(const std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    std::size_t remainder = vertices.size();

    for (auto it = vertices.begin(); remainder > 0; --remainder)
    {
        htd::vertex_t vertex = *it;

        auto & currentNeighborhood = availableNeighborhoods.at(vertex);

        ++it;

        ret += htd::set_intersection_size(it, vertices.end(), std::upper_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex), currentNeighborhood.end());
    }

    return ret;
}

const htd::LibraryInstance * htd::AdvancedMinFillOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::AdvancedMinFillOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::AdvancedMinFillOrderingAlgorithm * htd::AdvancedMinFillOrderingAlgorithm::clone(void) const
{
    return new htd::AdvancedMinFillOrderingAlgorithm(implementation_->managementInstance_);
}

#endif /* HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_CPP */
