#include "airport.h"
#include <sstream>
#include <algorithm>

void CAirport::load_from_string(const std::string &data)
{
    auto join = [](const std::vector<std::string>& v, int start_index, int end_index = -1, char delimiter = ' ') {
        auto out = std::string();
        
        if(end_index == -1)
            end_index = v.size();
        
        for(int i = start_index; i < end_index; i++) {
            out += v[i];

            if(i != end_index - 1)
                out += delimiter;
        }

        return out;
    };

    auto split = [](const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
    
        while(std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
    
        return tokens;
    };

    std::string no_comments;
    std::string processed;

    bool encountered_char = false;
    bool add_space = false;
    bool ignore_space = false;

    bool in_company = false;
    auto company = CAirtravel();

    for(auto line : split(data, '\n'))
        if(line.size() > 0)
            if(line[0] != '#')
                no_comments += line + "\n";
    
    for(char ch : no_comments) {
        if(ch == '\r' || ch == '\n') {
            ignore_space = true;
            continue;
        }

        if(std::isspace(ch)) {
            if(encountered_char) {
                add_space = true;
                encountered_char = false;
            }
        } else {
            if(add_space) {
                if(!ignore_space) processed += ' ';
                add_space = false;
            }

            ignore_space = false;
            encountered_char = true;
            processed += ch;
        }
    }

    for(auto statement : split(processed, ';')) {
        auto tokens = split(statement, ' ');
        auto instruction = tokens[0];

        if(instruction == "#")
            continue;

        if(instruction == "company") {
            if(tokens[1] == "begin")
                in_company = true;
            else {
                this->add_company(company);
                company = CAirtravel();
                in_company = false;
            }

            continue;
        }

        if(in_company) {
            if(instruction == "nationality")
                company.set_nationality(join(tokens, 1));

            if(instruction == "name")
                company.set_name(join(tokens, 1));

            if(instruction == "destination")
                company.add_destinations(join(tokens, 2), std::atoi(tokens[1].c_str()));

            if(instruction == "plane") {
                company.add_planes(
                    CPlane(join(tokens, 3), std::atoi(tokens[1].c_str())), 
                    std::atoi(tokens[2].c_str())
                );
            }

            continue;
        }

        if(instruction == "name") {
            this->name = join(tokens, 1);
            continue;
        }

        if(instruction == "flight") {
            this->flight_id = std::atoi(tokens[1].c_str());
            continue;
        }

        printf("Unknown instruction: %s\n", instruction.c_str());
        exit(EXIT_FAILURE);
    }
}

CAirport::CAirport(const std::string &name, unsigned int flight_id)
{
    this->name = name;
    this->flight_id = flight_id;
}

CAirport::CAirport(const std::string &file_path)
{
    auto file = fopen(file_path.c_str(), "r");
    
    if(!file) {
        perror("File read error");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    auto buffer = (char*)malloc(file_size + 1);
    
    if(!buffer) {
        perror("Out of memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    this->load_from_string(std::string(buffer));
    delete buffer;
}

void CAirport::add_company(const CAirtravel &company)
{
    this->companies.emplace_back(company);
}

std::vector<CAirtravel> CAirport::get_companies() const
{
    return this->companies;
}

void CAirport::set_flight_id(unsigned int flight_id)
{
    this->flight_id = flight_id;
}

unsigned int CAirport::get_flight_id() const
{
    return this->flight_id;
}

void CAirport::set_name(const std::string &name)
{
    this->name = name;
}

std::string CAirport::get_name() const
{
    return this->name;
}

std::string CAirport::get_company_with_most_flights() const
{
    unsigned int most_flights = 0;
    std::string output = "";

    for(auto company : this->companies) {
        unsigned int flights = 0;
        
        for(auto pair : company.get_planes())
            flights += pair.second;
        
        if(flights > most_flights) {
            most_flights = flights;
            output = company.get_name();
        }
    }

    return output;
}

std::string CAirport::get_plane_with_most_destinations() const
{
    std::map<std::string, unsigned int> map;
    unsigned int n = 0;
    std::string s;

    for(auto company : this->companies)
        for(auto pair : company.get_planes())
            map[pair.first.get_brand()] += pair.second;
    
    for(auto pair : map) {
        if(n < pair.second) {
            n = pair.second;
            s = pair.first;
        }
    }

    return s;
}

std::optional<std::string> CAirport::get_most_popular_destination(const std::string &company_name) const
{
    std::string name;
    unsigned int popularity = 0;

    const auto company =
        std::find_if(this->companies.begin(), this->companies.end(), [company_name](CAirtravel company) {
            return company.get_name() == company_name;
        });
    
    if(company == this->companies.end())
        return std::nullopt;

    for(auto pair : (*company).get_destinations()) {
        if(pair.second > popularity) {
            name = pair.first;
            popularity = pair.second;
        }
    }

    return std::optional{name};
}

std::set<CPlane> CAirport::planes_sofia_10000() const
{
    auto planes = std::set<CPlane>();

    for(auto company : this->companies) {
        bool flag = false;
        
        for(auto pair : company.get_destinations()) {
            if(pair.first == "Sofia") {
                flag = true; 
                break;
            }
        }

        if(!flag) continue;

        for(auto pair : company.get_planes())
            if(pair.first.get_hours_spent_flying() > 10000)
                planes.insert(pair.first);
    }

    return planes;
}

std::vector<CPlane> CAirport::planes_2000_10() const
{
    auto planes = std::vector<CPlane>();

    for(auto company : this->companies)        
        for(auto pair : company.get_planes())            
            if(pair.first.get_hours_spent_flying() < 2000 && pair.second > 10)
                planes.emplace_back(pair.first);

    return planes;
}

float CAirport::average_destination_count_french_airlines() const
{
    unsigned int n = 0;
    auto seen = std::list<std::string>();

    for(auto company : this->companies) {
        if(company.get_nationality() != "France") continue;

        for(auto pair : company.get_destinations()) {
            if(std::find(seen.begin(), seen.end(), pair.first) != seen.end())
                continue;
            
            n += pair.second;
            seen.emplace_back(pair.first);
        }
    }

    return (float)n / (float)seen.size();
}

std::optional<CAirport::PlaneInfo> CAirport::get_plane_info(const std::string &brand) const
{
    auto owners = std::vector<CAirtravel>();
    unsigned int flights = 0;
    bool seen = false;

    for(auto company : this->companies)
        for(auto pair : company.get_planes())
            if(pair.first.get_brand() == brand) {
                owners.emplace_back(company);
                flights += pair.second;
                seen = true;
            }
    
    if(!seen)
        return std::nullopt;

    auto plane_info = PlaneInfo();
    plane_info.flights = flights;
    plane_info.owners = owners;
    return std::optional{plane_info};
}
