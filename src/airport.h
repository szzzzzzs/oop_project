#include <string>
#include <vector>
#include <optional>
#include <set>
#include "airtravel.h"

class CAirport {
    private:
        std::string name;
        std::vector<CAirtravel> companies;
        unsigned int flight_id;

        void load_from_string(const std::string& data);
    public:
        CAirport(const std::string& name, unsigned int flight_id);
        CAirport(const std::string& file_path);

        void add_company(const CAirtravel& company);
        std::vector<CAirtravel> get_companies() const;
        
        void set_flight_id(unsigned int flight_id);
        unsigned int get_flight_id() const;

        void set_name(const std::string& name);
        std::string get_name() const;

        std::string get_company_with_most_flights() const;
        std::string get_plane_with_most_destinations() const;
        std::optional<std::string> get_most_popular_destination(const std::string& company) const;
        std::set<CPlane> planes_sofia_10000() const;
        std::vector<CPlane> planes_2000_10() const;
        float average_destination_count_french_airlines() const;

        struct PlaneInfo {
            unsigned int flights;
            std::vector<CAirtravel> owners;
        }; std::optional<PlaneInfo> get_plane_info(const std::string& brand) const;
};
