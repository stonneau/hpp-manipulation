// Copyright (c) 2014, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-manipulation.
// hpp-manipulation is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-manipulation is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-manipulation. If not, see <http://www.gnu.org/licenses/>.

#include "hpp/manipulation/graph/graph-component.hh"

namespace hpp {
  namespace manipulation {
    namespace graph {
      std::vector < GraphComponentWkPtr_t > GraphComponent::components = std::vector < GraphComponentWkPtr_t >();

      const std::string& GraphComponent::name() const
      {
        return name_;
      }

      void GraphComponent::name(const std::string& name)
      {
        name_ = name;
      }

      GraphComponentWkPtr_t GraphComponent::get(int id)
      {
# ifdef HPP_DEBUG
        if (id < 0 || id >= (int)components.size())
          throw std::out_of_range ("ID out of range.");
# endif // HPP_DEBUG
        return components[id];
      }

      int GraphComponent::id () const
      {
        return id_;
      }

      std::ostream& GraphComponent::print (std::ostream& os) const
      {
        os << id () << " : " << name ();
        return os;
      }

      void GraphComponent::addNumericalConstraint (const DifferentiableFunctionPtr_t& function)
      {
        numericalConstraints_.push_back(function);
      }

      void GraphComponent::addLockedDofConstraint (const LockedDofPtr_t& constraint)
      {
        lockedDofConstraints_.push_back (constraint);
      }

      const DifferentiableFunctions_t& GraphComponent::numericalConstraints() const
      {
        return numericalConstraints_;
      }

      const LockedDofs_t& GraphComponent::lockedDofConstraints () const
      {
        return lockedDofConstraints_;
      }

      void GraphComponent::parentGraph(const GraphWkPtr_t& parent)
      {
        graph_ = parent;
      }

      void GraphComponent::init (const GraphComponentWkPtr_t& weak)
      {
        wkPtr_ = weak;
        id_ = components.size();
        components.push_back (wkPtr_);
      }

      std::ostream& operator<< (std::ostream& os,
          const hpp::manipulation::graph::GraphComponent& graphComp)
      {
        return graphComp.print (os);
      }
    } // namespace graph
  } // namespace manipulation
} // namespace hpp