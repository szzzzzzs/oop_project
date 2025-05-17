#include "airport.h"
#include <iostream>
#include <set>

int main() {
    auto airport = CAirport("airport.txt");
    
    std::cout << "Welcome to " << airport.get_name() << std::endl;
    std::cout << "Flight ID: " << airport.get_flight_id() << std::endl;

    while(true) {
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Average number of destinations of French airliners" << std::endl;
        std::cout << "2. Planes with <2000 flight hours and >10 destinations" << std::endl;
        std::cout << "3. Print plane info" << std::endl;
        std::cout << "4. Print airliner with most flights" << std::endl;
        std::cout << "5. Print plane with most destinations" << std::endl;
        std::cout << "6. Get most popular destination for a given company" << std::endl;
        std::cout << "7. Print planes that have visited Sofia and have >10000 flight hours" << std::endl;

        std::string buffer;
        unsigned int n;
        
        while(true) {
            std::getline(std::cin, buffer);
            n = std::atoi(buffer.c_str());
            
            if(n >= 0 && n <= 7)
                break;
            
            std::cout << "Invalid input" << std::endl;
        }

        switch(n) {
            case 0: exit(EXIT_SUCCESS);

            case 1:
                std::cout << airport.average_destination_count_french_airlines() << std::endl;
                break;
            
            case 2:
                for(auto plane : airport.planes_2000_10())
                    plane.print();

                break;

            case 3:
                while(true) {
                    std::string plane_brand;
                    std::cout << "Plane brand and model:" << std::endl;
                    std::getline(std::cin, plane_brand);

                    auto maybe_plane_info = airport.get_plane_info(plane_brand);
                
                    if(!maybe_plane_info.has_value()) {
                        std::cout << "Plane not found" << std::endl;
                        continue;
                    }

                    auto plane_info = maybe_plane_info.value();
                    std::cout << "Flights: " << plane_info.flights << std::endl << "Owner(s): " << std::endl;

                    for(auto owner : plane_info.owners)
                        std::cout << owner.get_name() << " (" << owner.get_nationality() << ")" << std::endl;

                    break;
                }

                break;
            
            case 4:
                std::cout << airport.get_company_with_most_flights() << std::endl;
                break;
            
            case 5:
                std::cout << airport.get_plane_with_most_destinations() << std::endl;
                break;
            
            case 6:
                while(true) {
                    std::string company;
                    std::cout << "Company name:" << std::endl;
                    std::getline(std::cin, company);

                    auto maybe_company = airport.get_most_popular_destination(company);
                
                    if(!maybe_company.has_value()) {
                        std::cout << "Company not found" << std::endl;
                        continue;
                    }

                    std::cout << maybe_company.value() << std::endl;
                    break;
                }
                break;
            
            case 7:
                auto planes = airport.planes_sofia_10000();

                if(planes.size() != 0)
                    for(auto plane : planes)
                        plane.print();
                else
                    std::cout << "No planes found" << std::endl;

                break;
        }
    }

    return 0;
}