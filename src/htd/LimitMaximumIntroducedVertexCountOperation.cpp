/*
 * File:   LimitMaximumIntroducedVertexCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP
#define HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>

#include <algorithm>
#include <stdexcept>
#include <iterator>

/**
 *  Private implementation details of class htd::LimitMaximumIntroducedVertexCountOperation.
 */
struct htd::LimitMaximumIntroducedVertexCountOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager                           The management instance to which the current object instance belongs.
     *  @param[in] limit                            The maximum number of introduced vertices for a decomposition node.
     *  @param[in] treatLeafNodesAsIntroduceNodes   A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
     */
    Implementation(const htd::LibraryInstance * const manager, std::size_t limit, bool treatLeafNodesAsIntroduceNodes = false) : managementInstance_(manager), limit_(limit), treatLeafNodesAsIntroduceNodes_(treatLeafNodesAsIntroduceNodes)
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
     *  The maximum number of introduced vertices for a decomposition node.
     */
    std::size_t limit_;

    /**
     *  A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
     */
    bool treatLeafNodesAsIntroduceNodes_;
};

htd::LimitMaximumIntroducedVertexCountOperation::LimitMaximumIntroducedVertexCountOperation(const htd::LibraryInstance * const manager, std::size_t limit, bool treatLeafNodesAsIntroduceNodes) : implementation_(new Implementation(manager, limit, treatLeafNodesAsIntroduceNodes))
{
  
}

htd::LimitMaximumIntroducedVertexCountOperation::~LimitMaximumIntroducedVertexCountOperation()
{
  
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> introduceNodes;

    decomposition.copyIntroduceNodesTo(introduceNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = introduceNodes.begin(); it != introduceNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        if (implementation_->treatLeafNodesAsIntroduceNodes_ || !decomposition.isLeaf(node))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

            if (introducedVertexCount > implementation_->limit_)
            {
                std::vector<htd::vertex_t> introducedVertices;

                decomposition.copyIntroducedVerticesTo(introducedVertices, node);

                std::size_t remainder = introducedVertexCount % implementation_->limit_;

                introducedVertexCount -= remainder;

                std::size_t intermediatedVertexCount = introducedVertexCount / implementation_->limit_;

                if (intermediatedVertexCount > 0)
                {
                    intermediatedVertexCount--;
                }

                if (remainder == 0)
                {
                    intermediatedVertexCount--;
                }

                std::vector<htd::vertex_t> children;

                decomposition.copyChildrenTo(children, node);

                if (children.empty())
                {
                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                    htd::vertex_t newNode = decomposition.addChild(node);

                    decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                    decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(finish, implementation_->limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                            decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + implementation_->limit_)
                            {
                                std::advance(finish, implementation_->limit_);
                            }
                        }
                    }
                }
                else if (children.size() == 1)
                {
                    htd::vertex_t child = children[0];

                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.mutableBagContent(newNode) = newContent;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(start, implementation_->limit_);
                        std::advance(finish, implementation_->limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            for (auto it = start; it != finish; it++)
                            {
                                newContent.push_back(*it);
                            }

                            decomposition.mutableBagContent(newNode) = newContent;

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + implementation_->limit_)
                            {
                                std::advance(start, implementation_->limit_);
                                std::advance(finish, implementation_->limit_);
                            }
                        }
                    }
                }
            }
        }
    }
}


void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(graph, decomposition, labelingFunctions);
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> introduceNodes;

    decomposition.copyIntroduceNodesTo(introduceNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = introduceNodes.begin(); it != introduceNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        if (implementation_->treatLeafNodesAsIntroduceNodes_ || !decomposition.isLeaf(node))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

            if (introducedVertexCount > implementation_->limit_)
            {
                std::vector<htd::vertex_t> introducedVertices;

                decomposition.copyIntroducedVerticesTo(introducedVertices, node);

                std::size_t remainder = introducedVertexCount % implementation_->limit_;

                introducedVertexCount -= remainder;

                std::size_t intermediatedVertexCount = introducedVertexCount / implementation_->limit_;

                if (intermediatedVertexCount > 0)
                {
                    intermediatedVertexCount--;
                }

                if (remainder == 0)
                {
                    intermediatedVertexCount--;
                }

                std::vector<htd::vertex_t> children;

                decomposition.copyChildrenTo(children, node);

                if (children.empty())
                {
                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                    htd::vertex_t newNode = decomposition.addChild(node);

                    decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                    decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(finish, implementation_->limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                            decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + implementation_->limit_)
                            {
                                std::advance(finish, implementation_->limit_);
                            }
                        }
                    }
                }
                else if (children.size() == 1)
                {
                    htd::vertex_t child = children[0];

                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.mutableBagContent(newNode) = newContent;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(start, implementation_->limit_);
                        std::advance(finish, implementation_->limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            std::copy(start, finish, std::back_inserter(newContent));
                            std::inplace_merge(newContent.begin(), newContent.end() - std::distance(start, finish), newContent.end());

                            decomposition.mutableBagContent(newNode) = newContent;

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + implementation_->limit_)
                            {
                                std::advance(start, implementation_->limit_);
                                std::advance(finish, implementation_->limit_);
                            }
                        }
                    }
                }
                else
                {
                    throw std::logic_error("void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph &, htd::IMutableTreeDecomposition &) const");
                }
            }
        }
    }
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isIntroduceNode(vertex))
        {
            if (implementation_->treatLeafNodesAsIntroduceNodes_ || !decomposition.isLeaf(vertex))
            {
                std::vector<htd::vertex_t> bagContent;

                const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

                std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

                std::size_t introducedVertexCount = decomposition.introducedVertexCount(vertex);

                if (introducedVertexCount > implementation_->limit_)
                {
                    std::vector<htd::vertex_t> introducedVertices;

                    decomposition.copyIntroducedVerticesTo(introducedVertices, vertex);

                    std::size_t remainder = introducedVertexCount % implementation_->limit_;

                    introducedVertexCount -= remainder;

                    std::size_t intermediatedVertexCount = introducedVertexCount / implementation_->limit_;

                    if (intermediatedVertexCount > 0)
                    {
                        intermediatedVertexCount--;
                    }

                    if (remainder == 0)
                    {
                        intermediatedVertexCount--;
                    }

                    std::vector<htd::vertex_t> children;

                    decomposition.copyChildrenTo(children, vertex);

                    if (children.empty())
                    {
                        auto start = introducedVertices.begin();
                        auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                        htd::vertex_t newNode = decomposition.addChild(vertex);

                        decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                        htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                        newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                        decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (intermediatedVertexCount > 0)
                        {
                            std::advance(finish, implementation_->limit_);

                            for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                            {
                                newNode = decomposition.addParent(newNode);

                                decomposition.mutableBagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                                newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                                decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                                for (auto & labelingFunction : labelingFunctions)
                                {
                                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                                    delete labelCollection;

                                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                                }

                                if (index < introducedVertexCount + implementation_->limit_)
                                {
                                    std::advance(finish, implementation_->limit_);
                                }
                            }
                        }
                    }
                    else if (children.size() == 1)
                    {
                        htd::vertex_t child = children[0];

                        auto start = introducedVertices.begin();
                        auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : implementation_->limit_);

                        htd::vertex_t newNode = decomposition.addParent(child);

                        std::vector<htd::vertex_t> newContent;

                        const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                        std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                        decomposition.mutableBagContent(newNode) = newContent;

                        htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                        newInducedHyperedges.restrictTo(newContent);

                        decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        createdVertices.push_back(newNode);

                        if (intermediatedVertexCount > 0)
                        {
                            std::advance(start, implementation_->limit_);
                            std::advance(finish, implementation_->limit_);

                            for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                            {
                                newNode = decomposition.addParent(newNode);

                                std::copy(start, finish, std::back_inserter(newContent));
                                std::inplace_merge(newContent.begin(), newContent.end() - std::distance(start, finish), newContent.end());

                                decomposition.mutableBagContent(newNode) = newContent;

                                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                                newInducedHyperedges.restrictTo(newContent);

                                decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                                for (auto & labelingFunction : labelingFunctions)
                                {
                                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                    delete labelCollection;

                                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                                }

                                createdVertices.push_back(newNode);

                                if (index < introducedVertexCount + implementation_->limit_)
                                {
                                    std::advance(start, implementation_->limit_);
                                    std::advance(finish, implementation_->limit_);
                                }
                            }
                        }
                    }
                    else
                    {
                        throw std::logic_error("void htd::LimitMaximumIntroducedVertexCountOperation::apply(const htd::IMultiHypergraph &, htd::IMutableTreeDecomposition &) const");
                    }
                }
            }
        }
    }
}

bool htd::LimitMaximumIntroducedVertexCountOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::LimitMaximumIntroducedVertexCountOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::LimitMaximumIntroducedVertexCountOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::LimitMaximumIntroducedVertexCountOperation * htd::LimitMaximumIntroducedVertexCountOperation::clone(void) const
{
    return new htd::LimitMaximumIntroducedVertexCountOperation(implementation_->managementInstance_, implementation_->limit_, implementation_->treatLeafNodesAsIntroduceNodes_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::LimitMaximumIntroducedVertexCountOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::LimitMaximumIntroducedVertexCountOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::LimitMaximumIntroducedVertexCountOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP */
