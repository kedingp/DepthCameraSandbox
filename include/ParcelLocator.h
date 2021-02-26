#pragma once

namespace parcel_locator
{

template<class LocatorType, class InputType, class OutputType>
class ParcelLocator
{
public:
    OutputType findParcel(const InputType& input) { return static_cast<LocatorType*>(this)->findParcelImpl(input); };
};
} // namespace parcelLocator
