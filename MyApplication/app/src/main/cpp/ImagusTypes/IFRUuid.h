#pragma once
#include "ImagusCommonExports.h"
#include "ImagusTypes.h"
#include <string>
#include <functional>
#include <gsl/gsl-lite.h>



namespace boost
{
    namespace uuids
    {
        struct uuid;
    }
}


namespace Imagus
{
    IFR_UUID IMAGUSTYPESAPI GenIFR_UUID();
    //IFR_UUID IMAGUSTYPESAPI IFR_UUIDFromBoost(boost::uuids::uuid const & uuid);

    IFR_UUID IMAGUSTYPESAPI IFR_UUIDFromName(std::string const & nspace, std::string const & name);
    IFR_UUID IMAGUSTYPESAPI IFR_UUIDFromBoost(boost::uuids::uuid const & uuid);


    inline void uuid_to_string(IFR_UUID const & uid, std::string & str)
    {	// convert double to string
        str.resize(36);
        static const char * hex = "0123456789abcdef";
        size_t out = 0;
        for(size_t i = 0; i < 16; ++i)
        {
            str.at(out++) = hex[(uid.types.u8[i] >> 4) % 16];
            str.at(out++) = hex[uid.types.u8[i] % 16];
            if(i == 3 || i == 5 || i == 7 || i == 9)
            {
                str.at(out++) = '-';
            }
        }
    }

    inline std::string uuid_to_string(IFR_UUID const & uid)
    {	// convert double to string
        std::string str;
        uuid_to_string(uid, str);
        return str;
    }


    inline IFR_UUID  uuid_from_string(const char * str, size_t size)
    {
        IFR_UUID result;
        for(size_t i = 0, uuidIndex = 0; i < size && uuidIndex <= 15; uuidIndex++)
        {
            int c1 = toupper(str[i++]);
            c1 -= (c1 >= 'A') ? ('A' - 10) : '0';
            int c2 = toupper(str[i++]);
            c2 -= (c2 >= 'A') ? ('A' - 10) : '0';
            if(str[i] == '-')
            {
                ++i;
            }

            result.types.u8[uuidIndex] = (c2 & 15) + (c1 * 16);
        }
        return result;
    }
    /*
    inline IFR_UUID  uuid_from_string(std::string const & str)
    {
        return uuid_from_string(str.c_str(),str.size());
    }                             */

    inline IFR_UUID  uuid_from_string(gsl::cstring_span str)
    {
        return uuid_from_string(str.data(), str.size());
    }


}


template<class ArgumentType, class ResultType>
struct unary_function
{
    typedef ArgumentType argument_type;
    typedef ResultType result_type;
};


namespace std
{
    template<>
    struct hash<IFR_UUID> : public unary_function < IFR_UUID, int64_t >
    {
        int64_t operator()(const IFR_UUID & value) const
        {
            std::size_t seed = 0;
            std::hash<uint64_t> hasher;
            for(uint64_t u : value.types.u64)
            {
                seed ^= hasher(u) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    template<>
    struct equal_to<IFR_UUID> : public unary_function < IFR_UUID, bool >
    {
        bool operator()(const IFR_UUID & x, const IFR_UUID & y) const
        {
            if(x.types.u64[0] == y.types.u64[0] && x.types.u64[1] == y.types.u64[1])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    template<>
    struct not_equal_to<IFR_UUID> : public unary_function < IFR_UUID, bool >
    {
        bool operator()(const IFR_UUID & x, const IFR_UUID & y) const
        {
            if(!(x.types.u64[0] == y.types.u64[0] && x.types.u64[1] == y.types.u64[1]))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    inline string to_string(IFR_UUID const & uid)
    {	// convert double to string
        string str;
        Imagus::uuid_to_string(uid, str);
        return str;
    }

}
