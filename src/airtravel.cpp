#include "airtravel.h"
#include <iostream>

void CAirtravel::set_name(const std::string &name)
{
    this->name = name;
}

std::string CAirtravel::get_name() const
{
    return this->name;
}

void CAirtravel::set_nationality(const std::string &nationality)
{
    this->nationality = nationality;
}

std::string CAirtravel::get_nationality() const
{
    return this->nationality;
}

void CAirtravel::add_planes(const CPlane &plane, unsigned int destinations)
{
    this->planes[plane] += destinations;
}

std::map<CPlane, unsigned int> CAirtravel::get_planes() const
{
    return this->planes;
}

void CAirtravel::add_destinations(const std::string &destination, unsigned int flights)
{
    this->destinations.insert(std::make_pair(destination, flights));
}

std::multimap<std::string, unsigned int> CAirtravel::get_destinations() const
{
    return this->destinations;
}

CAirtravel::CAirtravel()
{
}

CAirtravel::CAirtravel(const std::string &name, const std::string &nationality)
{
    this->name = name;
    this->nationality = nationality;

    this->planes = std::map<CPlane, unsigned int>();
    this->destinations = std::multimap<std::string, unsigned int>();
}

std::list<CPlane> CAirtravel::planes_2000_10() const
{
    auto list = std::list<CPlane>();

    for(auto pair : this->planes)
        if(pair.first.get_hours_spent_flying() < 2000 && pair.second > 10)
            list.emplace_back(pair.first);
    
    return list;
}
