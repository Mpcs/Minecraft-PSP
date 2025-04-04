// Noise++ Library
// Copyright (c) 2008, Urs C. Hanselmann
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef NOISEPP_ABSOLUTE_H
#define NOISEPP_ABSOLUTE_H

#include "NoisePipeline.h"
#include "NoiseModule.h"

namespace noisepp {
    class AbsoluteElement1D : public PipelineElement1D {
    private:
        ElementID mElement;
        const PipelineElement1D *mElementPtr;

    public:
        AbsoluteElement1D(const Pipeline1D *pipe, ElementID element) : mElement(element) {
            mElementPtr = pipe->getElement(element);
        }

        virtual Real getValue(Real x, Cache *cache) const {
            Real value;
            value = getElementValue(mElementPtr, mElement, x, cache);
            return std::fabs(value);
        }
    };

    class AbsoluteElement2D : public PipelineElement2D {
    private:
        ElementID mElement;
        const PipelineElement2D *mElementPtr;

    public:
        AbsoluteElement2D(const Pipeline2D *pipe, ElementID element) : mElement(element) {
            mElementPtr = pipe->getElement(element);
        }

        virtual Real getValue(Real x, Real y, Cache *cache) const {
            Real value;
            value = getElementValue(mElementPtr, mElement, x, y, cache);
            return std::fabs(value);
        }
    };

    class AbsoluteElement3D : public PipelineElement3D {
    private:
        ElementID mElement;
        const PipelineElement3D *mElementPtr;

    public:
        AbsoluteElement3D(const Pipeline3D *pipe, ElementID element) : mElement(element) {
            mElementPtr = pipe->getElement(element);
        }

        virtual Real getValue(Real x, Real y, Real z, Cache *cache) const {
            Real value;
            value = getElementValue(mElementPtr, mElement, x, y, z, cache);
            return std::fabs(value);
        }
    };

    /** Module that outputs the absolute value of the input value from the source module.
        Calculates the absolute value of the value from the source module.
    */
    class AbsoluteModule : public SingleSourceModule<AbsoluteElement1D, AbsoluteElement2D, AbsoluteElement3D> {
    public:
        /// @copydoc noisepp::Module::getType()
        ModuleTypeId getType() const { return MODULE_ABSOLUTE; }
    };
};

#endif

