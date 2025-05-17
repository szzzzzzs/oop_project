#include "plane.h"
#include <random>
#include <iostream>

void CPlane::generate_id()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, INT32_MAX);
    this->id = distr(gen);    
}

std::string CPlane::get_brand() const
{
    return this->brand;
}

void CPlane::set_brand(const std::string &brand)
{
    this->brand = brand;
}

unsigned int CPlane::get_hours_spent_flying() const
{
    return this->hours_spent_flying;
}

void CPlane::set_hours_spent_flying(unsigned int n)
{
    this->hours_spent_flying = n;
}

CPlane::CPlane()
{
    generate_id();
}

CPlane::CPlane(const std::string &brand, unsigned int hours_spent_flying)
{
    this->brand = brand;
    this->hours_spent_flying = hours_spent_flying;
    generate_id();
}

bool CPlane::operator<(const CPlane &other) const
{
    return this->id < other.id;
}

void CPlane::print() const
{
    std::cout << this->brand << " [" << this->hours_spent_flying << " hrs]" << std::endl; 
}