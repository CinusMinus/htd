/*
 * File:   ConnectedComponentAlgorithmFactory.hpp
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

#ifndef HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP
#define HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/AlgorithmFactory.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IConnectedComponentAlgorithm interface.
     */
    class ConnectedComponentAlgorithmFactory : public htd::AlgorithmFactory<htd::IConnectedComponentAlgorithm>
    {
        public:
            /**
             *  Constructor for the factory class.
             *
             *  @param[in] manager   The management instance to which the new factory class belongs.
             */
            HTD_API ConnectedComponentAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API ConnectedComponentAlgorithmFactory(const ConnectedComponentAlgorithmFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API ConnectedComponentAlgorithmFactory & operator=(const ConnectedComponentAlgorithmFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~ConnectedComponentAlgorithmFactory();

            /**
             *  Create a new IConnectedComponentAlgorithm object.
             *
             *  @return A new IConnectedComponentAlgorithm object.
             */
            HTD_API htd::IConnectedComponentAlgorithm * createInstance(void) const override;
    };
}

#endif /* HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
