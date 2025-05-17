#include <string>
#include <map>
#include <list>
#include "plane.h"

class CAirtravel {
    private:
        std::string name;
        std::string nationality;

        std::multimap<std::string, unsigned int> destinations;
        std::map<CPlane, unsigned int> planes;

    public:
        void set_name(const std::string& name);
        std::string get_name() const;

        void set_nationality(const std::string& nationality);
        std::string get_nationality() const;

        void add_planes(const CPlane& plane, unsigned int destinations);
        std::map<CPlane, unsigned int> get_planes() const;

        void add_destinations(const std::string& destination, unsigned int flights);
        std::multimap<std::string, unsigned int> get_destinations() const;

        CAirtravel();
        CAirtravel(const std::string& name, const std::string& nationality);

        std::list<CPlane> planes_2000_10() const;
};
