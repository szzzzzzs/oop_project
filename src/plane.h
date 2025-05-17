#include <string>

class CPlane {
    private:
        unsigned int id;
        std::string brand;
        unsigned int hours_spent_flying;

        void generate_id();
    public:
        std::string get_brand() const;
        void set_brand(const std::string& brand);

        unsigned int get_hours_spent_flying() const;
        void set_hours_spent_flying(unsigned int n);

        CPlane();
        CPlane(const std::string& brand, unsigned int hours_spent_flying);
        bool operator <(const CPlane& other) const;

        void print() const;
};